#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {true,  false, false, false};
    bool varying(4) b = {true,  false, false, true};
    bool varying(4) c = {false, true,  true,  true};
    bool varying(4) d = {true,  true,  false, true};

    int varying(4) x = {0, 1, 2, 3};

    if ( a || b )   // < T, F, F, T >
    {
      // cm = < T, F, F, T >
      if ( c && d )   // < F, T, F, T >
      {
        // cm = < F, F, F, T >
        x += 5;
      }
      else
      {
        // cm = < T, F, F, F >
        x += 1;
      }
    }
    else
    {
      // cm = < F, T, T, F >
      x += 9;
    }

		return unify( x, 1, 10, 11, 8 );
}

// $RESULT: 15 = 0b1111
