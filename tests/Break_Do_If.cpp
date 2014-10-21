#include "test.h"

int main()
{
  int varying(4) n = 0;

  int varying(4) i = { 0, 1, 2, 3 };
  do
  {
    if ( i > 2 )
      break;
    ++n;
    i += 4;
  }
  while ( i < 10 );

  return ( unify( i, 4, 5, 6, 3 ) << 4 ) | unify( n, 1, 1, 1, 0 );
}

// $RESULT: 255 = 0b1111 1111
