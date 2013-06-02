#include "sierra.h"
#include <iostream>

int main()
{
    bool varying(4) a = {true, true, false, true};
    bool varying(4) b = {false, false, false, true};

    int x = 0;

    if ( a || b )
        x++;

    std::cout << x << std::endl;

    return 0;
}
