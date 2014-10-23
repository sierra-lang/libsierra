#include "test.h"

int main()
{
  int varying(4) i = { 0, 1, 2, 3 };
  int varying(4) j = { 0, 1, 2, 3 };

    while ( i < 8 )
    {
      while ( j < 20 )  // 2nd it: i = {4, 5, 6, 7}
      {
        if ( j >= i )
          break;
        j = j * 2 + 1;    // 2nd it: j = {0, 1, 2, 3} -> {1, 3, 5, 7} -> {3, 7, 11, 7} -> {7, 7, 11, 7}
      }

      i += 4;
    }
    // i = {8, 9, 10, 11}


    return ( unify( i, 8, 9, 10, 11 ) << 4 ) | unify( j, 7, 7, 11, 7 );
}

// $RESULT: 255 = 0b1111 1111
