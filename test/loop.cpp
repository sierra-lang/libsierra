// this program demonstrates the useless conversion problem
// clang++ loop.cpp -mavx -O3 -I.. -DL=8 -fsierra -S -o -
#include "sierra/defines.h"

int varying(L) f(int varying(L) n) {
    int varying(L) i = 0;
    while  (i < n)
        ++i;
    return i;
}
