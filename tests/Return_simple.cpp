#include "test.h"

spmd(4)
int varying(4) foo()
{
  int varying(4) r = { 0, 1, 2, 3 };
  return r;
}

int main()
{
  auto r = foo();

  return unify( r, 0, 1, 2, 3 );
}

// $RESULT: 15 = 0b1111
