#include "sierra/defines.h"
#include "test.h"

int main()
{
    int varying(4) l = 0;

    int varying(4) n;
    for ( n = {0, 1, 2, 3}; n < 6; n += 4 )
      l += 1;


    return ( unify( n, 8, 9, 6, 7 ) << 4 ) | unify( l, 2, 2, 1, 1 );
}

// $RESULT: 255 = 0b1111 1111
