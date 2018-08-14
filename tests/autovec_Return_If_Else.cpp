#include "test.h"

spmd(4) int foo() {
  bool b = true;

  if ( b )
    return 42;
  else
    return 13;
}

int main() {
  int varying(4) r = foo();

  return unify( r, 42, 42, 13, 13 );
}

// $RESULT: 15 = 0b1111
