#include "sierra/defines.h"
#include "test.h"

int main()
{
  int varying(4) i = {5, -3, 0, 0};
  int varying(4) n = 0;

  if ( i )
    ++n;
  else
    --n;


  return unify( n, 1, 1, -1, -1 );
}

// $RESULT: 15 = 0b1111
