#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {false, true, false, false};

    int varying(4) x = {0, 1, 2, 3};

    if ( ! a ) // < T, F, T, T >
        x++;
    else
        x--;

    return unify( x, 1, 0, 3, 4 );
}

// $RESULT: 15 = 0b1111
