#include "sierra/defines.h"
#include "test.h"

int main()
{
  bool varying(4) cond0 = {true, true, false, false};
  bool varying(4) cond1 = {true, false, false, true};
  int  varying(4) two   = 2;
  int  varying(4) three = 3;
  int  varying(4) four  = 4;

  auto x = cond0 ? (cond1 ? two : three) : four;

  return unify(x, 2, 3, 4, 4);
}

// $RESULT: 15
