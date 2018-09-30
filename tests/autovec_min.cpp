#include "test.h"

float _min(float a, float b) {
    return a < b ? a : b;
}

int main() {
    int b = 2;
    int varying(4) c = {0, 9, 3, 1};
    int varying(4) d = _min(b, c);
    return unify(d, 0, 2, 2, 1);
}

// $RESULT: 15 = 0b1111
