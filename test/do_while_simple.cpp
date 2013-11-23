#include "sierra/defines.h"

int main ( )
{
    int varying (4) a = 3;
    do
    {
        a = a + 1;
    }
    while( a < 4 );
    return 0;
}
