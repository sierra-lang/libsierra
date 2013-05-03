#include <iostream>
#include "sierra.h"

#define TYPE int
#define LENGTH 4

template<class T, int L>
void print( T varying(L) );

int main ()
{
    // a = <0,1,1,1>
    TYPE varying(LENGTH) a = 1;
    sierra::insert<TYPE, LENGTH>( a, 0, 0);

    // b = <0,1,1,1>
    TYPE varying(LENGTH) b = a;
    sierra::insert<TYPE, LENGTH>( b, 1, 0);

    std::cout << "a: ";
    print( a );

    std::cout << "b: ";
    print( b );

    if ( a )
    {
        /*
        if ( b )
        {

        }
        else
        {
            std::cout << "x";
        }
        */
    }
}

// Prints a vector type in a human readable format
template<class T, int L>
void print( T varying(L) vec )
{
    std::cout << "<";
    for ( int i = 0; i < L ; i++ )
    {
        std::cout << sierra::extract<T, L>( vec, i );
        if ( i != L - 1 )
            std::cout << ",";
    }
    std::cout << ">\n";
}
