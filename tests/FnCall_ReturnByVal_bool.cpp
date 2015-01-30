#include "test.h"
#include <iostream>

bool varying(4) foo()
{
  return {true, true, false, true};
}

int main()
{
  auto ret = foo();
  return unify(ret, true, true, false, true);
}

// $RESULT: 15 = 0b1111
