#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {true, true, false, false};
    int  varying(4) x = a ? 0 : 3;

    return unify(x, 0, 0, 3, 3);
}

// $RESULT: 15 = 0b1111
