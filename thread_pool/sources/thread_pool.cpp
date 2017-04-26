#include "thread_pool.hpp"
#include <chrono>
#include <cstdlib>

void probability_calculator::operator() ( int probability )
{
    std::cout << std::this_thread::get_id() << std::endl;
    std::random_device rd;
    std::mt19937 random_gen( rd() );
    std::uniform_int_distribution<> r1( 0, 100 );

    if ( probability >= r1( random_gen ) )
        std::cout << std::error_code ( 404, xmpp_category() ).message() << std::endl;
    else
        std::cout << std::error_code ( 0, xmpp_category() ).message() << std::endl;
}
//-----------------------------------------------------------------------------------------------------------
thread_pool::thread_pool( int thread_num ) :
    work_lck( work_mtx ),
    stop_flag( 0 )
{
    for ( int i = 0; i < thread_num; i++ )
    {
        threads.emplace( &thread_pool::run, this );
    }
}

void thread_pool::run()
{
    while ( true )
    {
        int stop = stop_flag.load( std::memory_order_relaxed );

        if ( stop == 1 )
            break;

        queue_mtx.lock();

        if ( postponed.empty() == true )
        {
            queue_mtx.unlock();
            handlers.wait_for( work_lck,  std::chrono::milliseconds( 20 ) );

        } else
        {
            std::function<void()> current = postponed.front();
            postponed.pop();

            if ( postponed.empty() == false )
                handlers.notify_all();

            queue_mtx.unlock();

            if ( current == NULL )
            {
                break;
            }

            current();
        }
    }
}

thread_pool::~thread_pool()
{
    int thread_num = threads.size();
    stop_flag.store( 1, std::memory_order_relaxed );
    handlers.notify_all();

    while ( threads.empty() == false )
    {
        threads.front().join();
        threads.pop();
    }
}

void thread_pool::push( std::function<void()> handler )
{
    queue_mtx.lock();
    postponed.push( handler );
    queue_mtx.unlock();

    handlers.notify_one();
}
