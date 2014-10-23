#include "test.h"
#include <cstdio>

int main()
{
  int n = 0;
  int varying(4) i = { 0, 1, 2, 3 };
  for ( ; i < 10 ; )
  {
    if ( i > 2 )
      break;
    ++n;
    i += 4;
  }

  return ( n << 4 ) | unify( i, 4, 5, 6, 3 );
}

// $RESULT: 31 = 0b1 1111
