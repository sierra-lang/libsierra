#include "sierra/defines.h"
#include "test.h"

int main()
{
  int  varying(4) a = {true, true, false, false};
  int  varying(4) b = {0, 1, 2, 3};
  int  varying(4) c = 5;

  auto x = a ? b : c;

  return unify( x, 0, 1, 5, 5 );
}

// $RESULT: 15
