#include "test.h"
#include <cstdlib>

void foo(float &v)
{
    v = 0.42f;
}

int main()
{
  float varying(4) v = {-3.f, .5f, .7f, 4.2f};
  foo(v);
  return unify(v, 0.42f, 0.42f, 0.42f, 0.42f);
}

// $RESULT: 15 = 0b1111
