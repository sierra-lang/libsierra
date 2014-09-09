#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {true, false, false, false};
    bool varying(4) b = {false, false, false, true};
    bool varying(4) c = {false, true, false, true};

    int varying(4) x = {0, 1, 2, 3};

    if ( a || b || c )	// < T, T, F, T >
        x++;
    else
        x--;

    return unify( x, 1, 2, 1, 4 );
}

// $RESULT: 15 = 0b1111
