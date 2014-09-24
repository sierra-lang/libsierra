#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {true, true, false, false};
    bool varying(4) b = {true, false, false, true};

    int varying(4) x = a || b;

    return unify( x, true, true, false, true );
}

// $RESULT: 15 = 0b1111
