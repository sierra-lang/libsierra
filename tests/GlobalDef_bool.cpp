#include "test.h"

bool varying(4) v = {true, false, false, true};

int main()
{
  return unify(v, true, false, false, true);
}

// $RESULT: 15 = 0b1111
