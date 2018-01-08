#include "test.h"

int varying(4) foo(int varying(4) r) {
  return r;
}

int main() {
  int varying(4) a = { 0, 1, 2, 3 };
  auto r = foo(a);

  return unify( r, 0, 1, 2, 3 );
}

// $RESULT: 15 = 0b1111
