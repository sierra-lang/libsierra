#include "test.h"
#include <cstdlib>

void foo(bool varying(4) v)
{
  exit(unify(v, true, false, false, true));
}

int main()
{
  bool varying(4) v = {true, false, false, true};
  foo(v);
  return -1;
}

// $RESULT: 15 = 0b1111
