#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {true, true, false, false};
    bool varying(4) b = {true, false, false, true};
    bool varying(4) c = {false, true, false, true};

    int varying(4) x = a ? b : c;

    return unify( x, true, false, false, true );
}

// $RESULT: 15 = 0b1111
