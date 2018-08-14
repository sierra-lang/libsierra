#include "test.h"
#include <iostream>

spmd(4)
int foo()
{
  return 3;
}

int main()
{
  int varying(4) ret = 5;

  bool varying(4) mask = {true, false, false, true};
  if (mask)
    ret = foo();

  return unify(ret, 3, 5, 5, 3);
}

// $RESULT: 15 = 0b1111
