#include "sierra.h"
#include "sierra_ostream.h"

#include <iostream>

struct vec3 {
    float x, y, z;
};

spmd(4) 
void add4(vec3 varying(4)& res, const vec3 varying(4)& v, const vec3 varying(4)& w) {
    res.x = v.x + w.x;
    res.y = v.y + w.y;
    res.z = v.z + w.z;
}

int main() {
    vec3 varying(4) a;
    vec3 varying(4) b;
    a.x = (float varying(4)) {0, 1, 2, 3};
    a.y = (float varying(4)) {0, 1, 2, 3};
    a.z = (float varying(4)) {0, 1, 2, 3};
    b.x = (float varying(4)) {0, 1, 2, 3};
    b.y = (float varying(4)) {0, 1, 2, 3};
    b.z = (float varying(4)) {0, 1, 2, 3};
    vec3 varying(4) c;
    c.x = c.y = c.z = 0;

    if ((bool varying(4)){false, false, true, true})
        add4(c, a, b);

    std::cout << c.x << std::endl;
}
