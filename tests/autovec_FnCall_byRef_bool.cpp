#include "test.h"
#include <cstdlib>

void foo(bool &v) {
    v = true;
}

int main() {
  bool varying(4) v = {true, false, false, true};
  foo(v);
  return unify(v, true, true, true, true);
}

// $RESULT: 15 = 0b1111
