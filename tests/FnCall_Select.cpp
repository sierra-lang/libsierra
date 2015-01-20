#include "test.h"
#include <iostream>

void dump(int varying(4) &v)
{
  int *vp = (int *) &v;
  std::cout << vp[0] << " " << vp[1] << " " << vp[2] << " " << vp[3] << std::endl;
}

int varying(4) foo(int varying(4) cond, int varying(4) a, int varying(4) b)
{
  dump(cond);
  dump(a);
  dump(b);
  int varying(4) v = cond ? a : b;
  dump(v);
  return v;
}

int main()
{
  int varying(4) cond = {true, true, false, true};
  int varying(4) a    = {0, 1, 2, 3};

  auto r = foo(cond, a, 5);

  return unify(r, 0, 1, 5, 3);
}

// $RESULT: 15 = 0b1111
