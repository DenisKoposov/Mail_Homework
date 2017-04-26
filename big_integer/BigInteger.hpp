#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <functional>

typedef long long int llint_t ;

class BigInteger
{
private:
    std::vector<llint_t> value; // inside-out order
public:

    int sign;
    llint_t base;
    //Constructors
    BigInteger();
    BigInteger( llint_t input );
    BigInteger( std::string input );
    //Copy, move, swap, assign
    BigInteger( const BigInteger& obj );
    BigInteger( BigInteger&& obj );
    void swap( BigInteger& b );
    BigInteger& operator = ( BigInteger const& num );
    BigInteger& operator = ( BigInteger&& num );
    //Destructor
    ~BigInteger() = default;
    //Interface
    std::vector<llint_t>& valueRef();
    const std::vector<llint_t>& constValueRef() const;
    //Unary minus
    BigInteger operator - ( );
};
//Output
std::ostream& operator << ( std::ostream& os, BigInteger& a );
std::string&  operator << ( std::string& str, BigInteger& a );
//Binary math operations
BigInteger operator + ( BigInteger& a, BigInteger& b );
BigInteger operator - ( BigInteger& a, BigInteger& b );
BigInteger operator * ( BigInteger& a, BigInteger& b );
//Comparisons
bool operator >  ( BigInteger& a, BigInteger& b );
bool operator <= ( BigInteger& a, BigInteger& b );
bool operator <  ( BigInteger& a, BigInteger& b );
bool operator >= ( BigInteger& a, BigInteger& b );
bool operator == ( BigInteger& a, BigInteger& b );
bool operator != ( BigInteger& a, BigInteger& b );
#endif // BIGINTEGER_HPP
