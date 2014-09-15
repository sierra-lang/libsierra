#include "sierra/defines.h"
#include "test.h"

int main()
{
    int varying(4) l = 0;

    int varying(4) n = { 0, 1, 2, 3 };
    do
    {
      l += 1;
      n += 1;
    }
    while ( n < 2 );


    return ( unify( n, 2, 2, 3, 4 ) << 4 ) | unify( l, 2, 1, 1, 1 );
}

// $RESULT: 255 = 0b1111 1111
