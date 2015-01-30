#include "test.h"
#include <iostream>

int varying(4) select(int varying(4) cond, int varying(4) a, int varying(4) b)
{
  int varying(4) x;

  if (cond)
    x = a;
  else
    x = b;

  return x;
}

int main()
{
  int varying(4) cond = {true, true, false, true};
  int varying(4) a    = {0, 1, 2, 3};

  auto r = select(cond, a, 5);

  return unify(r, 0, 1, 5, 3);
}

// $RESULT: 15 = 0b1111
