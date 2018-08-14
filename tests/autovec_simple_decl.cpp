#include "test.h"

int foo() {
  int varying(4) r = { 0, 1, 2, 3 };
  return r;
}

int main() {
  int varying(4) r = foo();

  return unify( r, 0, 1, 2, 3 );
}

// $RESULT: 15 = 0b1111
