// boost::variant tutorial adapted from:
// http://www.boost.org/doc/libs/1_55_0/doc/html/variant/tutorial.html

/* Sample compilation and run:
kuyu@ub16:~/dkuyu/Dropbox/practice/cpp/boost/variant/tutorial$ g++ -I/home/kuyu/dkuyu/bin/boost_1_60_0 -std=c++14 variant.cpp
kuyu@ub16:~/dkuyu/Dropbox/practice/cpp/boost/variant/tutorial$ ./a.out
hello
hello world!
hello world! hello world!
hi there! hi there!
greetings from mars! greetings from mars!
42
salutations salutations
*/

#include <iostream>
#include <string>
#include <vector>
#include <boost/variant.hpp>

void times_two( boost::variant< int, std::string > & operand )
{
    if ( int* pi = boost::get<int>( &operand ) )
        *pi *= 2;
    else if ( std::string* pstr = boost::get<std::string>( &operand ) )
        *pstr += *pstr;
}

class times_two_visitor
    : public boost::static_visitor<>
{
public:

    void operator()(int & i) const
    {
        i *= 2;
    }

    void operator()(std::string & str) const
    {
        str += str;
    }

};

class times_two_generic
    : public boost::static_visitor<>
{
public:

    template <typename T>
    void operator()( T & operand ) const
    {
        operand += operand;
    }

};

int main()
{
    boost::variant< int, std::string > v;
    v = "hello";
    std::cout << v << std::endl;

    std::string& str = boost::get<std::string>(v);
    str += " world! ";
    std::cout << v << std::endl;

    times_two(v);
    std::cout << v << std::endl;

    v = "hi there! ";
    boost::apply_visitor( times_two_visitor(), v );
    std::cout << v << std::endl;

    v = "greetings from mars! ";
    boost::apply_visitor( times_two_generic(), v );
    std::cout << v << std::endl;

    std::vector< boost::variant<int, std::string> > vec;
    vec.push_back( 21 );
    vec.push_back( "salutations " );

    times_two_generic visitor;
    std::for_each(vec.begin(), vec.end(), boost::apply_visitor(visitor));
    std::for_each(vec.begin(), vec.end(), [](auto val){ std::cout << val << std::endl;});

    return 0;
}
