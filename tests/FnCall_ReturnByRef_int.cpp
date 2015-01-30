#include "test.h"
#include <iostream>

void foo(int varying(4) &ret)
{
  ret = {0, 1, 2, 3};
}

int main()
{
  int varying(4) ret;
  foo(ret);

  return unify(ret, 0, 1, 2, 3);
}

// $RESULT: 15 = 0b1111
