#include <string>
#include "thread_pool.hpp"

int main()
{
    thread_pool pool( 5 );

    while ( true )
    {
        int probability;
        std::string data;
        std::cin >> data;

        if ( data.find( "stop" ) != std::string::npos )
            break;
        try
        {
            probability = stoi( data );

            if ( probability < 0 || probability > 100 )
            {
                std::cout << "Incorrect data" << std::endl;
                continue;
            }
        }
        catch ( std::invalid_argument )
        {
            std::cout << "Incorrect data" << std::endl;
            continue;
        }
        catch ( std::out_of_range )
        {
            std::cout << "Incorrect data" << std::endl;
            continue;
        }

        probability_calculator calculator;

        pool.push( std::bind( calculator, probability ) );
    }

    return 0;
}
