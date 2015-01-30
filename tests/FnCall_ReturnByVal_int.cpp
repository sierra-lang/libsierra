#include "test.h"
#include <iostream>

int varying(4) foo()
{
  return {0, 1, 2, 3};
}

int main()
{
  auto ret = foo();
  return unify(ret, 0, 1, 2, 3);
}

// $RESULT: 15 = 0b1111
