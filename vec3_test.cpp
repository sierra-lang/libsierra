#include "vec3.h"
#include "sierra_ostream.h"

#include <iostream>

using namespace sierra;

int main() {
    vec3 varying(4) a;
    vec3 varying(4) b;
    a.x = (float varying(4)) {1, 1, 2, 3};
    a.y = (float varying(4)) {0, 1, 2, 3};
    a.z = (float varying(4)) {0, 1, 2, 3};
    b.x = (float varying(4)) {0, 1, 2, 3};
    b.y = (float varying(4)) {0, 1, 2, 3};
    b.z = (float varying(4)) {0, 1, 2, 3};
    vec3 varying(4) c;
    c.x = c.y = c.z = (float varying(4)){0, 0, 0, 0};

    if ((bool varying(4)){false, false, true, true})
        c = add<4>(a, b);

    std::cout << c.x << std::endl;
}
