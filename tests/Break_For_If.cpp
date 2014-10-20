#include "test.h"

int main()
{
  int varying(4) n = 0;

  int varying(4) i;
  for ( i = { 0, 1, 2, 3 }; i < 10; i += 4 )
  {
    if ( n > 2 )
      break;
    ++n;
  }

  //return ( unify( i, 4, 5, 6, 3 ) << 4 ) | unify( n, 1, 1, 1, 0 );;
  return ( (int *) &i )[0];
}

// $RESULT: 255 = 0b1111 1111
