#include "test.h"

int main()
{
    int varying(4) n = 0;

    int varying(4) i = { 0, 1, 2, 3 };
    while ( i < 6 )
    {
      i += 4;
      continue;
      ++n;
    }
    
		return ( unify( i, 8, 9, 6, 7 ) << 4 ) | unify( n, 0, 0, 0, 0 );
}

// $RESULT: 255 = 0b1111 1111
