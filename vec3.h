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
    res.x = v.x + v.x;
    res.y = v.y + v.y;
    res.z = v.z + v.z;
    return res;
}

spmd(4) 
vec3 varying(4) add4(vec3 varying(4) v, vec3 varying(4) w) {
    vec3 varying(4) res;
    res.x = v.x + v.x;
    res.y = v.y + v.y;
    res.z = v.z + v.z;
    return res;
}

}

#endif
