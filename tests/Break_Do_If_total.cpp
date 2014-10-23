#include "test.h"

int main()
{
    int varying(4) n = { 0, 1, 2, 3 };
    do
    {
      if ( n % 2 )
        break;
      else
        break;
      ++n;
    }
    while ( ( bool varying(4) ) true );


    return unify( n, 0, 1, 2, 3 );
}

// $RESULT: 15 = 0b1111
