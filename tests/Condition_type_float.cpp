#include "sierra/defines.h"
#include "test.h"

int main()
{
  float varying(4) f = {3.f, -1.5f, 0, 0};
  int varying(4) n = 0;

  if ( f )
    ++n;
  else
    --n;


  return unify( n, 1, 1, -1, -1 );
}

// $RESULT: 15 = 0b1111
