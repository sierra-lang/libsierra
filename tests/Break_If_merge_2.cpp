#include "test.h"

int main()
{
    int varying(4) n = { 0, 1, 2, 3 };
    while ( ( bool varying(4) ) true )
    {
      if ( n % 2 )
        break;
      else
        ++n;
    }

    return unify( n, 1, 1, 3, 3 );
}

// $RESULT: 15 = 0b1111
