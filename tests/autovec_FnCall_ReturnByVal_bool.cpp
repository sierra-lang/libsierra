#include "test.h"
#include <iostream>

bool foo()
{
  return true;
}

int main()
{
  bool varying(4) ret = foo();
  return unify(ret, true, true, true, true);
}

// $RESULT: 15 = 0b1111
