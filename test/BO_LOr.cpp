#include "sierra/defines.h"
//#include <iostream>

int main()
{
    bool varying(4) a = {true, true, false, true};
    bool varying(4) b = {false, false, false, true};

    int varying(4) x = {0, 1, 2, 3};

    /*
    for ( int i = 0; i < 4; i++ )
        std::cout << sierra::extract<int,4>( x, i ) << "\t";
    std::cout << std::endl;
    */

    if ( a || b )
        x++;
    else
        x--;

    /*
    for ( int i = 0; i < 4; i++ )
        std::cout << sierra::extract<int,4>( x, i ) << "\t";
    std::cout << std::endl;
    */

    return 0;
}
