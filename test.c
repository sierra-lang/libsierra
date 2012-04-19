#include <stdbool.h>

typedef float xmm __attribute__ ((sierra_vector(4)));
typedef float ymm __attribute__ ((sierra_vector(8)));
typedef bool mask __attribute__ ((sierra_vector(4)));
typedef  int ixmm __attribute__ ((sierra_vector(4)));

void test() {
    ixmm a, b;
    xmm m;
    /*m = a < b;*/
    m + a;
}

void f(xmm a, xmm b, ymm c, ymm d) {
    int e, f;
    if (a < b) {
        if (e < f) {
            if (c < d) {
            }
        }
    }
}
