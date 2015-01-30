#include "test.h"

int varying(4) v = {0, 1, 2, 3};

int main()
{
  return unify(v, 0, 1, 2, 3);
}

// $RESULT: 15 = 0b1111
