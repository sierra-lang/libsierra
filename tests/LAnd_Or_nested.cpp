#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {true,  true,  true,  false};
    bool varying(4) b = {true,  false, true,  true};
    bool varying(4) c = {false, true,  false, true};
    bool varying(4) d = {true,  true,  false, true};

    int varying(4) x = {0, 1, 2, 3};

    if ( a && b )   // < T, F, T, F >
    {
      // cm = < T, F, T, F >
      if ( c || d )   // < T, T, F, T >
      {
        // cm = < T, F, F, F >
        x += 5;
      }
      else
      {
        // cm = < F, F, T, F >
        x += 1;
      }
    }
    else
    {
      // cm = < F, T, F, T >
      x += 9;
    }

		return unify( x, 5, 10, 3, 12 );
}

// $RESULT: 15 = 0b1111
