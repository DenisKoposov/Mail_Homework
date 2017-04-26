#include <BigInteger.hpp>
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#define default_base 1000
#define base_width 3
#define DEBUG

BigInteger::BigInteger()
    : base ( default_base ),
      sign ( 0 ),
      value( 1, 0 )
{
    #ifdef DEBUG
        std::cout << " constr_default " << std::endl;
    #endif // DEBUG
}

BigInteger::BigInteger( llint_t input )
    : base ( default_base )
{
    #ifdef DEBUG
        std::cout << " constr_short " << std::endl;
    #endif // DEBUG
    sign = 1;

    if ( input < 0 )
    {
        sign = -1;
        input = -input;
    }

    value.clear();

    if ( input == 0 )
    {
        value.push_back( 0 );
        sign = 0;
    }

    while ( input > 0 )
    {
        value.push_back( input % base );
        input = input / base;
    }
}

BigInteger::BigInteger( std::string input )
    : base ( default_base )
{

    #ifdef DEBUG
        std::cout << " constr_string " << std::endl;
    #endif // DEBUG
    std::string part;
    size_t copied = 0;
    size_t len = input.length();
    size_t found = input.find('-');
    size_t parts = 0;
    size_t remainder = 0;

    if ( found != std::string::npos )
    {
        copied++;
        sign = -1;
        parts = ( len - 1 ) / base_width;

        if ( ( remainder = ( len - 1 ) % base_width ) != 0 )
            parts++;
    } else
    {
        sign = 1;
        parts = len / base_width;

        if ( ( remainder = len % base_width ) != 0 )
            parts++;
    }

    value.resize( parts, 0 );
    int i = parts - 1;

    if ( remainder != 0 )
    {
        part = input.substr( copied, remainder );
            value.at( i ) = stoll( part, NULL,  10 );
        i--;
        copied += remainder;
    }

    bool isZero = true;

    if ( value.at(i) != 0 )
            isZero = false;

    while ( i >= 0 )
    {
        part = input.substr( copied, base_width );
        value.at(i) = stoll( part, NULL,  10 );

        if ( value.at(i) != 0 )
            isZero = false;
        i--;
        copied += base_width;
    }

    if ( isZero == true )
        sign = 0;
}

//BigInteger::~BigInteger()
//{
//    std::cout << " destr " << std::endl;
//}

std::vector<llint_t>& BigInteger::valueRef()
{
    return value;
}

const std::vector<llint_t>& BigInteger::constValueRef() const
{
    return value;
}

//Copy, swap, assign
BigInteger::BigInteger( const BigInteger& obj ) // copy
    : sign( obj.sign ),
      base( obj.base ),
      value ( obj.constValueRef() )
{
    #ifdef DEBUG
        std::cout << " copy " << std::endl;
    #endif // DEBUG
}

BigInteger::BigInteger( BigInteger&& obj )  // move without copying
{
    #ifdef DEBUG
        std::cout << " move " << std::endl;
    #endif // DEBUG

    this->swap( obj );
}

void BigInteger::swap( BigInteger& b ) // swap
{
    std::swap( b.valueRef(), value );
    std::swap( b.sign, sign );
    std::swap( b.base, base );
}

BigInteger& BigInteger::operator = ( BigInteger const& num ) // assign
{
    #ifdef DEBUG
        std::cout << " assign " << std::endl;
    #endif // DEBUG

    BigInteger copied( num );
    copied.swap( *this );
    return *this;
}

BigInteger& BigInteger::operator = ( BigInteger&& num ) // assign without copying
{
    #ifdef DEBUG
        std::cout << " assign_nocopy " << std::endl;
    #endif // DEBUG

    num.swap( *this );
    return *this;
}

BigInteger BigInteger::operator -(  )
{
    BigInteger rev_a ( *this );
    rev_a.sign = -this->sign;
    return rev_a;
}
//Output
std::ostream& operator  << ( std::ostream& os, BigInteger& a )
{
    if ( a.sign < 0 )
        os << "-";

    if ( a.sign == 0 )
    {
        os << "0";
        return os;
    }

    os << a.valueRef().back();

    os.fill( '0' );

    for ( int i = a.valueRef().size() - 2; i >= 0; i--)
    {
        os.width( 3 );
        os << a.valueRef().at(i);
    }

    return os;
}

std::string& operator << ( std::string& str, BigInteger& a )
{
    std::ostringstream oss;

    if ( a.sign < 0 )
        oss << "-";

    if ( a.sign == 0 )
    {
        oss << "0";
        str += oss.str();
        return str;
    }

    oss << a.valueRef().back();

    oss.fill( '0' );

    for ( int i = a.valueRef().size() - 2; i >= 0; i--)
    {
        oss.width( 3 );
        oss << a.valueRef().at(i);
    }

    str += oss.str();
    return str;
}

BigInteger operator + ( BigInteger& a, BigInteger& b )
{
    BigInteger c ( a );
//Same signs
    if ( a.sign == b.sign )
    {
        if ( c.valueRef().size() < b.valueRef().size() )
            c.valueRef().resize( b.valueRef().size(), 0 );

        for ( size_t i = 0; i < c.valueRef().size(); i++ )
        {
            if ( i < b.valueRef().size() )
                c.valueRef().at(i) += b.valueRef().at(i);

            if ( c.valueRef().at(i) >= default_base )
            {
                c.valueRef().at(i) -= default_base;

                if ( i + 1 == c.valueRef().size() )
                    c.valueRef().resize( i + 2, 0 );

                c.valueRef().at(i + 1)++;
            }
        }

        while ( c.valueRef().at( c.valueRef().size() - 1 ) == 0 && c.valueRef().size() > 1 )
        c.valueRef().pop_back();

        return c;
    }
// Different signs
    if ( c.valueRef().size() < b.valueRef().size() )
        c.valueRef().resize( b.valueRef().size(), 0 );

    for ( int i = 0; i < c.valueRef().size(); i++ )
    {
        if ( i < a.valueRef().size() && i < b.valueRef().size() )
        {
            c.valueRef().at(i) = a.sign * a.valueRef().at(i) +
                                 b.sign * b.valueRef().at(i);
            continue;
        }

        if ( i < a.valueRef().size() )
        {
            c.valueRef().at(i) = a.sign * a.valueRef().at(i);
            continue;
        }

        if ( i < b.valueRef().size() )
        {
            c.valueRef().at(i) = b.sign * b.valueRef().at(i);
            continue;
        }
    }

    c.sign = 0;

    for ( int i = c.valueRef().size() - 1; i >= 0; i-- )
    {
        if ( c.valueRef().at(i) > 0 )
        {
            c.sign = 1;
            break;
        }

        if ( c.valueRef().at(i) < 0 )
        {
            c.sign = -1;
            break;
        }
    }

    if ( c.sign == 0 )
    {
        c.valueRef().clear();
        c.valueRef().resize(1, 0);
        return c;
    }

    if ( c.sign > 0 )
    {
        for ( size_t i = 0; i < c.valueRef().size() - 1; i++ )
        {
            if ( c.valueRef().at(i) < 0 )
            {
                c.valueRef().at(i + 1)--;
                c.valueRef().at(i) += c.base;
            }
        }
    } else
    {
        for ( size_t i = 0; i < c.valueRef().size() - 1; i++ )
        {
            if ( c.valueRef().at(i) > 0 )
            {
                c.valueRef().at(i + 1)++;
                c.valueRef().at(i) -= c.base;
            }
        }
    }

    while ( c.valueRef().at( c.valueRef().size() - 1 ) == 0 && c.valueRef().size() > 1 )
        c.valueRef().pop_back();

    for ( size_t i = 0; i < c.valueRef().size() ; i++ )
        c.valueRef().at(i) *= c.sign;

    return c;
}
BigInteger operator - ( BigInteger& a, BigInteger& b )
{
    BigInteger rev_b (-b);
    return a + rev_b;
}
BigInteger operator * ( BigInteger& a, BigInteger& b )
{
    BigInteger c;
    c.valueRef().clear();
    c.valueRef().resize( a.valueRef().size() + b.valueRef().size(), 0 );

    for ( int i = 0; i < a.valueRef().size(); i++ )
    {
        for ( int j = 0; j < b.valueRef().size(); j++ )
        {
            llint_t tmp = a.valueRef().at(i) * b.valueRef().at(j);
            c.valueRef().at(i + j) += tmp % default_base;
            c.valueRef().at(i + j + 1) += tmp / default_base;

            if ( c.valueRef().at(i + j) >= default_base )
            {
                llint_t tmp2 = c.valueRef().at(i + j) / default_base;
                c.valueRef().at(i + j + 1) += tmp2;
                c.valueRef().at(i + j) -= tmp2 * default_base;
            }
        }

    }

    while ( c.valueRef().at( c.valueRef().size() - 1 ) == 0 && c.valueRef().size() > 1 )
        c.valueRef().pop_back();

    c.sign = a.sign * b.sign;
    return c;
}

// Comparisons
bool operator > ( BigInteger& a, BigInteger& b )
{
    if ( a.sign > b.sign )
        return true;

    if ( a.sign < b.sign )
        return false;

    if ( a.sign == 0 )
        return false;

    size_t a_size = a.valueRef().size();
    size_t b_size = b.valueRef().size();

    if ( a.sign > 0 )
    {
        if ( a_size > b_size )
            return true;

        if ( a_size < b_size )
            return false;

        for ( int i = a_size - 1; i >= 0; i--)
        {
            if ( a.valueRef().at(i) > b.valueRef().at(i) )
                return true;
            if ( a.valueRef().at(i) < b.valueRef().at(i) )
                return false;
        }
    }

    if ( a.sign < 0 )
    {
        if ( a_size > b_size )
            return false;

        if ( a_size < b_size )
            return true;

        for ( int i = a_size - 1; i >= 0; i--)
        {
            if ( a.valueRef().at(i) > b.valueRef().at(i) )
                return false;

            if ( a.valueRef().at(i) < b.valueRef().at(i) )
                return true;
        }
    }
    return false;
}

bool operator == ( BigInteger& a, BigInteger& b )
{
    if ( a.sign != b.sign )
        return false;

    size_t a_size = a.valueRef().size();
    size_t b_size = b.valueRef().size();

    if ( a_size != b_size )
        return false;

    for ( int i = 0; i < a_size; i++ )
    {
        if ( a.valueRef().at(i) != b.valueRef().at(i) )
        {
            return false;
        }
    }

    return true;
}

bool operator <= ( BigInteger& a, BigInteger& b )
{
     return !(a > b);
}

bool operator < ( BigInteger& a, BigInteger& b )
{
    return b > a;
}

bool operator >= ( BigInteger& a, BigInteger& b )
{
    return !(a < b);
}

bool operator != ( BigInteger& a, BigInteger& b )
{
    return !(a == b);
}

