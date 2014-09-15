#include "sierra/defines.h"
#include "test.h"

int main()
{
  double varying(4) d = {3., -1.5, 0, 0};
  int varying(4) n = 0;

  if ( d )
    ++n;
  else
    --n;


  return unify( n, 1, 1, -1, -1 );
}

// $RESULT: 15 = 0b1111
