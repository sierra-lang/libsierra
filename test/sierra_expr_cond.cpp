#include "sierra.h"

int main()
{
    bool varying(4) a = true;
    bool varying(4) b = false;

    if ( a || b )
        return 1;
    return 0;
}
