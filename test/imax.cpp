#define L 16
#include "sierra/math.h"

using namespace sierra;

int varying(L) foo(int varying(L) a, int varying(L) b) {
    //return sierra::imin(sierra::imax(a, 1), 0);
    return sierra::imin(a, b);
}
