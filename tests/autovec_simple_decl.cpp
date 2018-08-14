#include "test.h"

int foo() {
  int r = 0;
  return r;
}

int main() {
  int varying(4) r = foo();

  return unify( r, 0, 0, 0, 0 );
}

// $RESULT: 15 = 0b1111
