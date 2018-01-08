#include "test.h"

int varying(4) sum(int varying(2) a, int varying(2) b)
{
  int varying(2) c = a + b;
  a = c;
  return 1;
}

int main()
{
  int varying(2) a = {42, 42};
  auto r = sum(a, a);

  return unify( r, 1, 1, 1, 1 );
}

// $RESULT: 15 = 0b1111
