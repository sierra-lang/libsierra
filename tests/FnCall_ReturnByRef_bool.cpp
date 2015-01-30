#include "test.h"
#include <iostream>

void foo(bool varying(4) &ret)
{
  ret = {true, true, false, true};
}

int main()
{
  bool varying(4) ret;
  foo(ret);

  return unify(ret, true, true, false, true);
}

// $RESULT: 15 = 0b1111
