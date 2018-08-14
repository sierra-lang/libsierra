#include "test.h"
#include <iostream>

int select(int cond, int a, int b)
{
  int x;

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

  int varying(4) r = select(cond, a, 5);

  return unify(r, 0, 1, 5, 3);
}

// $RESULT: 15 = 0b1111
