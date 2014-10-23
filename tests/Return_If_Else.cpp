#include "test.h"

spmd(4)
int varying(4) foo()
{
  bool varying(4) b = { true, true, false, false };

  if ( b )
    return 42;
  else
    return 13;
}

int main()
{
  auto r = foo();

  return unify( r, 42, 42, 13, 13 );
}

// $RESULT: 15 = 0b1111
