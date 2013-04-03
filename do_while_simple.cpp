#include "../libsierra/sierra.h"

int varying(4) f  ( int varying(4) a )
{
    do
    {
        a = a + 1;
    }
    while( a < 4 );
    return a;
}
