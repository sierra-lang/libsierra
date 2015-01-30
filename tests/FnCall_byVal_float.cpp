#include "test.h"
#include <cstdlib>

void foo(float varying(4) v)
{
  exit(unify(v, -3.f, .5f, .7f, 4.2f));
}

int main()
{
  float varying(4) v = {-3.f, .5f, .7f, 4.2f};
  foo(v);
  return -1;
}

// $RESULT: 15 = 0b1111
