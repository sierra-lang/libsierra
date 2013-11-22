#include "sierra_ostream.h"

#define L 4
#include "vec3.h"
#include <iostream>

using namespace sierra;

int main() {
    vec3 varying(4) a;
    vec3 varying(4) b;
    vec3 varying(4) c;

    spmd_mode(4) {
        create(a, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3});
        create(b, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3});
        create(c, (float varying(4)) {0, 0, 0, 0}, (float varying(4)) {0, 0, 0, 0}, (float varying(4)) {0, 0, 0, 0});
    }

    if ((bool varying(4)){false, false, true, true})
        add(c, a, b);

    std::cout << c.x << std::endl;
}
