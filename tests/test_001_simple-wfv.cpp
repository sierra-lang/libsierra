// Shapes: T_TrT, LaunchCode: foo2f8

#include "test.h"

//extern "C"
float varying(8) foo(float varying(8) a, float varying(8) b) {
    float varying(8) x = a + b;
    float varying(8) y = x * x - b;
    return x / y;
}
