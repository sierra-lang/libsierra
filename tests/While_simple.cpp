#include "test.h"

int main()
{
    int varying(4) l = 0;

    int varying(4) n = { 0, 1, 2, 3 };
    while ( n < 6 )
    {
      l += 1;
      n += 4;
    }


    return ( unify( n, 8, 9, 6, 7 ) << 4 ) | unify( l, 2, 2, 1, 1 );
}

// $RESULT: 255 = 0b1111 1111
