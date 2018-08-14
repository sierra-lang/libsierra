#include "test.h"

int sum(int a, int b)
{
  int c = a + b;
  a = c;
  return 1;
}

int main()
{
  int varying(2) a = {42, 42};
  int varying(2) r = sum(a, a);

  return unify( r, 1, 1 );
}

// $RESULT: 15 = 0b1111
