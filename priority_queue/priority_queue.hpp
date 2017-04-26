#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
//Boost libraries
#include <boost/function.hpp>
#include <boost/asio.hpp>
//STL containers
#include <queue>

class PriorityQueue
{
private:
    class queuedHandler
    {
    public:
        queuedHandler( int p, boost::function<void()> f ) :
            p_( p ),
            f_( f )
        {}

        void operator()()
        {
            //std::cerr << "Queue layer" << std::endl;
            f_();
        }

        friend bool operator<( const queuedHandler& a,
                               const queuedHandler& b )
        {
            return a.p_ < b.p_;
        }

    private:
        int p_;
        boost::function<void()> f_;
    };

    std::priority_queue<queuedHandler> q_;
    boost::asio::io_service& service_;

    PriorityQueue();// Default constructor is private
public:
    // PriorityQueue constructor
    PriorityQueue( boost::asio::io_service& service ) :
        service_( service )
    {}
    // Add handler to the priority queue
    void push( int p, boost::function<void()> f )
    {
        q_.push( queuedHandler( p, f ) );
    }
    /* Execute all pushed handlers sequentially
       in accordance with their priorities*/
    void executeAll()
    {
        while ( !q_.empty() )
        {
            queuedHandler handler = q_.top();
            handler();
            q_.pop();
        }
    }

    void start()
    {
        while ( service_.run_one() )
        {
            while ( service_.poll_one() );
            this->executeAll();
        }
    }
    // Wrapped_handler
    template <typename Handler>
    class wrappedHandler
    {
    //private:
    public:
        PriorityQueue& q_;
        int p_;
        Handler h_;
        wrappedHandler(); // Default constructor is restricted
    public:
        wrappedHandler( PriorityQueue& q, int p, Handler h ) :
            q_( q ),
            p_( p ),
            h_( h )
        {}

        void operator()()
        {
            //std::cerr << p_ << ". ";
            h_();
        }

        template<typename Function>
        void pushWrapped( Function f )
        {
            q_.push( p_, f );
        }
    };
    // Wrapping function
    template <typename Handler>
    wrappedHandler<Handler> wrap( int priority, Handler handler )
    {
        return wrappedHandler<Handler>( *this, priority, handler );
    }
};

// Custom intermediate handler invocation
template <typename Function, typename Handler>
void asio_handler_invoke( Function f,
                          PriorityQueue::wrappedHandler<Handler>* h )
{
    //std::cerr << "Pushing function to the queue" << std::endl;
    h->pushWrapped( f );
}

#endif //PRIORITY_QUEUE_H
