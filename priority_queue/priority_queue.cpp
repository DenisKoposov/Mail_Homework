#include <iostream>

#include <priority_queue.hpp>

int main( int argc, char** argv )
{
    boost::asio::io_service service;
    PriorityQueue pq( service );

    service.post( pq.wrap( 11, []() {std::cerr << "10 most influential people in the world" << std::endl;} ) );
    service.post( pq.wrap( 10, []() {std::cerr << "Vladimir Putin -- A Russian President" << std::endl;} ) );
    service.post( pq.wrap( 2, []() {std::cerr << "Liliane Bettencourt -- L'Oreal owner" << std::endl;} ) );
    service.post( pq.wrap( 6, []() {std::cerr << "Angela Merkel -- A Germany Cancelor" << std::endl;} ) );
    service.post( pq.wrap( 3, []() {std::cerr << "Сhristine Lagarde" << std::endl;} ) );
    service.post( pq.wrap( 8, []() {std::cerr << "Xi Jinping -- A Chinese President" << std::endl;} ) );
    service.post( pq.wrap( 4, []() {std::cerr << "Bill Gates -- Microsoft founder" << std::endl;} ) );
    service.post( pq.wrap( 5, []() {std::cerr << "Mario Draghi -- A European Central Bank Chairman" << std::endl;} ) );
    service.post( pq.wrap( 1, []() {std::cerr << "Larry Page" << std::endl;} ) );
    service.post( pq.wrap( 9, []() {std::cerr << "Barak Obama -- An American President" << std::endl;} ) );
    service.post( pq.wrap( 7, []() {std::cerr << "Francis -- Pope of Rome" << std::endl;} ) );

    pq.start();

    return 0;
}
