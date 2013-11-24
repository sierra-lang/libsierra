#include "sierra/sierra.h"
#include "sierra/ostream.h"

#include <iostream>

#define L 4
#include "sierra/vec3.h"
#undef L

#define L 8
#include "sierra/vec3.h"
#undef L

using namespace sierra;

int main() {
    vec3 varying(4) a;
    vec3 varying(4) b;
    vec3 varying(4) c;
    vec3 varying(4) foo;
    vec3 bar;

    spmd_mode(4) {
        create(a, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3});
        create(b, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3}, (float varying(4)) {0, 1, 2, 3});
        create(c, (float varying(4)) {0, 0, 0, 0}, (float varying(4)) {0, 0, 0, 0}, (float varying(4)) {0, 0, 0, 0});
    }

    if ((bool varying(4)){false, false, true, true}) {
        add(c, a, b);
        normalize(c);
        splat(foo, bar);
    }


    std::cout << c.x << std::endl;
    std::cout << c.y << std::endl;
    std::cout << c.z << std::endl;
}
