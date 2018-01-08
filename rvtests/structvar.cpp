#include "test.h"

typedef struct ss ss;
struct ss {
    int a, b;
};

int main(void) {
    ss varying(4) x;
    ss varying(4) y;
    //x.a = 42;
    //x.b = 42;
    //y = x;
    return 0;
}

