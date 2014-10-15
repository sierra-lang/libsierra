#include "test.h"

int main()
{
    int varying(4) n = 0;

    int varying(4) i;
    for ( i = { 0, 1, 2, 3 }; i < 10; i += 4 )
    {
      break;
      ++n;
    }
    
    return ( unify( i, 0, 1, 2, 3 ) << 4 ) | unify( n, 0, 0, 0, 0 );;
}

// $RESULT: 255 = 0b1111 1111
