#ifndef SIERRA_VEC3_H
#define SIERRA_VEC3_H

#include "sierra.h"

namespace sierra {

struct vec3 {
    float x, y, z;
};

template<int L>
spmd(L) 
vec3 varying(L) add(vec3 varying(L) v, vec3 varying(L) w) {
    vec3 varying(L) res;
    res.x = v.x + w.x;
    res.y = v.y + w.y;
    res.z = v.z + w.z;
    return res;
}

spmd(4) 
vec3 varying(4) add4(vec3 varying(4) v, vec3 varying(4) w) {
    vec3 varying(4) res;
    res.x = v.x + w.x;
    res.y = v.y + w.y;
    res.z = v.z + w.z;
    return res;
}

}

#endif
