#include "test.h"

int main()
{
  int varying(4) n = {1,2,3,4};

label:
  while ( n < 4 )
  {
    n = n * 3;
    goto label;
    n = 100;
  }

  return unify( n, 9, 6, 9, 4 );
}

// $RESULT: 15 = 0b1111
