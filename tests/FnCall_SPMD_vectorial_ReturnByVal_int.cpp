#include "test.h"
#include <iostream>

spmd(4)
int varying(4) foo()
{
  return {0, 1, 2, 3};
}

int main()
{
  int varying(4) ret = 5;

  bool varying(4) mask = {true, false, false, true};
  if (mask)
    ret = foo();

  return unify(ret, 0, 5, 5, 3);
}

// $RESULT: 15 = 0b1111
