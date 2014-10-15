#include "test.h"

int main()
{
    int varying(4) a = { true, true, false, true };
    int varying(4) b = { false, true, false, true };
    int varying(4) c = { true, true, false, false };

    int varying(4) n = 0;

    if ( a )  // T, T, F, T
    {
      if ( b )  // F, T, F, T
      {
        if ( c )  // F, T, F, F
          ++n;
        ++n;
      }
      ++n;
    }
    else  // F, F, T, F
    {
      if ( c )  // F, F, F, F
        n = 0;
      --n;
    }

    return unify( n, 1, 3, -1, 2 );
}

// $RESULT: 15 = 0b1111
