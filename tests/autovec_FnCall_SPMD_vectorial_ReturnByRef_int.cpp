#include "test.h"
#include <iostream>

spmd(4)
void foo(int &ret)
{
  ret = 42;
}

int main()
{
  int varying(4) ret = 5;

  bool varying(4) mask = {true, false, false, true};
  if (mask)
    foo(ret);

  return unify(ret, 42, 5, 5, 42);
}

// $RESULT: 15 = 0b1111
