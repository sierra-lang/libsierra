#include "test.h"

int main()
{
    int varying(4) a = { true, true, false, true };
    int varying(4) b = { false, true, false, true };

    int varying(4) n = 0;

    if ( a )  // T, T, F, T
    {
      if ( b )  // F, T, F, T
        ++n;
      ++n;
    }

    return unify( n, 1, 2, 0, 2 );
}

// $RESULT: 15 = 0b1111
