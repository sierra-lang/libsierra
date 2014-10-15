#include "test.h"

int main()
{
    int varying(4) n = 0;

    int varying(4) i = { 0, 1, 2, 3 };
    while ( bool varying(4) mask = true )
    {
      i += 4;
			if ( i > 10 )
				break;
      ++n;
    }
    
		return ( unify( i, 12, 13, 14, 11 ) << 4 ) | unify( n, 2, 2, 2, 1 );;
}

// $RESULT: 255 = 0b1111 1111
