#ifndef SIERRA_VEC3_H
#define SIERRA_VEC3_H

#include "sierra.h"

namespace sierra {

struct vec3 {
    float x, y, z;
};

spmd(L) void create(vec3 varying(L)& res, float varying(L) x, float varying(L) y, float varying(L) z) {
    res.x = x;
    res.y = y;
    res.z = z;
}

// binary operators

spmd(L) void add(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x + W.x;
    res.y = v.y + W.y;
    res.z = v.z + W.z;
}

spmd(L) void sub(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x - W.x;
    res.y = v.y - W.y;
    res.z = v.z - W.z;
}

spmd(L) void mul(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x * W.x;
    res.y = v.y * W.y;
    res.z = v.z * W.z;
}

spmd(L) void div(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x / W.x;
    res.y = v.y / W.y;
    res.z = v.z / W.z;
}

// in-place binary operators

spmd(L) void add_assign(vec3 varying(L)& res, const vec3 varying(L)& v) {
    res.x += v.x;
    res.y += v.y;
    res.z += v.z;
}

spmd(L) void sub_assign(vec3 varying(L)& res, const vec3 varying(L)& v) {
    res.x -= v.x;
    res.y -= v.y;
    res.z -= v.z;
}

spmd(L) void mul_assign(vec3 varying(L)& res, const vec3 varying(L)& v) {
    res.x *= v.x;
    res.y *= v.y;
    res.z *= v.z;
}

spmd(L) void div_assign(vec3 varying(L)& res, const vec3 varying(L)& v) {
    res.x /= v.x;
    res.y /= v.y;
    res.z /= v.z;
}

}

#endif
