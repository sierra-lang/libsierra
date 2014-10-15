#include "test.h"

int main()
{
    int varying(4) b = { true, true, false, true };
    int varying(4) n = { 0, 1, 2, 3 };

    if ( b )
      ++n;

    return unify( n, 1, 2, 2, 4 );
}

// $RESULT: 15 = 0b1111
