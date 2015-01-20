#include "sierra/defines.h"
#include "test.h"

int main()
{
    bool varying(4) a = {true, true, false, false};
    int  varying(4) b = {0, 1, 2, 3};

    int varying(4) x = a ? b : 5;

    return unify(x, 0, 1, 5, 5);
}

// $RESULT: 15 = 0b1111
