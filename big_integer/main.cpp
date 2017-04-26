#include <gtest/gtest.h>
#include <iostream>
#include <BigInteger.hpp>
#include <string>

#define default_base 1000
#define base_width 3

TEST( CONSTRUCTION_TEST_GROUP, DEFAULT_CONSTRUCTION )
{
    BigInteger a;
    ASSERT_EQ( a.sign, 0 );
    ASSERT_EQ( a.base, default_base );
    ASSERT_EQ( a.valueRef().size(), 1 );
    ASSERT_EQ( a.valueRef().at(0), 0 );

    SUCCEED();
}

TEST( CONSTRUCTION_TEST_GROUP, FROM_STRING_CONSTRUCTION )
{
    std::string test_string = "-1234567890";
    BigInteger a( test_string );
    std::string output;
    output << a;
    ASSERT_STREQ( test_string.data(), output.data() );

    test_string.clear();
    test_string = "128935617823658172635871263518726351982375";
    BigInteger b ( test_string );
    output.clear();
    output << b;
    ASSERT_STREQ( test_string.data(), output.data() );

    SUCCEED();
}

TEST( CONSTRUCTION_TEST_GROUP, FROM_SHORT_CONSTRUCTION )
{
    llint_t test_int = 13658123859;
    BigInteger a( test_int );
    std::string output;
    output << a;
    ASSERT_STREQ( std::to_string( test_int ).data(), output.data() );

    test_int = 123452;
    BigInteger b( test_int );
    output.clear();
    output << b;
    ASSERT_STREQ( std::to_string( test_int ).data(), output.data() );

    SUCCEED();
}

TEST( ARITHMETICS_TEST, ADDITION )
{
    BigInteger a ( "1835618736518726358719623578" );
    BigInteger b ( "13265178623587162358162358716238" );
    BigInteger sum;
    sum = a + b;
    std::string output;
    output << sum;
    ASSERT_STREQ( output.data(), "13267014242323681084521078339816" );

    SUCCEED();
}

TEST( ARITHMETICS_TEST, SUBSTRACTION )
{
    BigInteger a ( "1835618736518726358719623578" );
    BigInteger b ( "13265178623587162358162358716238" );
    BigInteger sub;
    sub = a - b;
    std::string output;
    output << sub;
    ASSERT_STREQ( output.data(), "-13263343004850643631803639092660" );

    SUCCEED();
}

TEST( ARITHMETICS_TEST, MULTIPLICATION )
{
    BigInteger a ( "1835618736518726358719623578" );
    BigInteger b ( "13265178623587162358162358716238" );
    BigInteger mul;
    mul = a * b;
    std::string output;
    output << mul;
    ASSERT_STREQ( output.data(),
    "24349810424724284558895525118998541115779407285502676259564" );

    SUCCEED();
}

TEST( COMPARISON_TEST, MULTIPLICATION )
{
    BigInteger a ( "1835618736518726358719623578" );
    BigInteger b ( "1835618736518726358719623578" );
    BigInteger c ( "7354623456123561354723415213" );

    ASSERT_TRUE ( a == b );
    ASSERT_FALSE( a == c );
    ASSERT_FALSE( c == a );
    ASSERT_TRUE ( a >= b );
    ASSERT_TRUE ( c >= b );
    ASSERT_FALSE( a >= c );
    ASSERT_TRUE ( a <= b );
    ASSERT_TRUE ( a <= c );
    ASSERT_FALSE( c <= a );
    ASSERT_FALSE( a > c );
    ASSERT_FALSE( a > b );
    ASSERT_TRUE ( c > a );
    ASSERT_TRUE ( a < c );
    ASSERT_FALSE( c < a );
    ASSERT_FALSE( a < b );
    ASSERT_TRUE ( a != c);
    ASSERT_FALSE( a != b);

    SUCCEED();
}

int main( int argc, char** argv )
{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
