#include "test.h"

int main()
{
    int varying(4) n = { 0, 1, 2, 3 };
    while ( ( bool varying(4) ) true )
    {
      if ( n % 2 )
        ++n;
      else
        break;
    }

    return unify( n, 0, 2, 2, 4 );
}

// $RESULT: 15 = 0b1111
