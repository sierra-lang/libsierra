#include "test.h"

int main()
{
  int varying(4) n = {1,2,3,4};

  if ( n % 2 )
    goto label;

  if ( n > 2 )
    goto label;

  ++n;

label:
  return unify( n, 1, 3, 3, 4 );
}

// $RESULT: 15 = 0b1111
