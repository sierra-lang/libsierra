#include "sierra/defines.h"
#include "test.h"

int main()
{
  bool varying(4) b = {true, true, false, false};
  int varying(4) n = 0;

  if ( b )
    ++n;
  else
    --n;


  return unify( n, 1, 1, -1, -1 );
}

// $RESULT: 15 = 0b1111
