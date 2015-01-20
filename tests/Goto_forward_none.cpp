#include "test.h"

int main()
{
  int varying(4) n = {1,2,3,4};

  if ( 0 == n )
    goto label;

  ++n;

label:
  return unify( n, 2, 3, 4, 5 );
}

// $RESULT: 15 = 0b1111
