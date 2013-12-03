#ifndef SIERRA_VEC3_H
#define SIERRA_VEC3_H

#include "defines.h"
#include "math.h"

namespace sierra {

struct vec3 {
    float x, y, z;
};

spmd(L) void copy(vec3 varying(L)& res, const vec3 varying(L)& v) {
    res.x = v.x;
    res.y = v.y;
    res.z = v.z;
}

spmd(L) void create(vec3 varying(L)& res, float varying(L) x, float varying(L) y, float varying(L) z) {
    res.x = x;
    res.y = y;
    res.z = z;
}

// binary operators - with vec3s

spmd(L) void add(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x + w.x;
    res.y = v.y + w.y;
    res.z = v.z + w.z;
}

spmd(L) void sub(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x - w.x;
    res.y = v.y - w.y;
    res.z = v.z - w.z;
}

spmd(L) void mul(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x * w.x;
    res.y = v.y * w.y;
    res.z = v.z * w.z;
}

spmd(L) void div(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.x / w.x;
    res.y = v.y / w.y;
    res.z = v.z / w.z;
}

// binary operators - with floats

spmd(L) void add(vec3 varying(L)& res, const vec3 varying(L)& v, float varying(L) f) {
    res.x = v.x + f;
    res.y = v.y + f;
    res.z = v.z + f;
}

spmd(L) void sub(vec3 varying(L)& res, const vec3 varying(L)& v, float varying(L) f) {
    res.x = v.x - f;
    res.y = v.y - f;
    res.z = v.z - f;
}

spmd(L) void mul(vec3 varying(L)& res, const vec3 varying(L)& v, float varying(L) f) {
    res.x = v.x * f;
    res.y = v.y * f;
    res.z = v.z * f;
}

spmd(L) void div(vec3 varying(L)& res, const vec3 varying(L)& v, float varying(L) f) {
    res.x = v.x / f;
    res.y = v.y / f;
    res.z = v.z / f;
}

// in-place binary operators - with vec3s

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

// in-place binary operators - with floats

spmd(L) void add_assign(vec3 varying(L)& res, float varying(L) f) {
    res.x += f;
    res.y += f;
    res.z += f;
}

spmd(L) void sub_assign(vec3 varying(L)& res, float varying(L) f) {
    res.x -= f;
    res.y -= f;
    res.z -= f;
}

spmd(L) void mul_assign(vec3 varying(L)& res, float varying(L) f) {
    res.x *= f;
    res.y *= f;
    res.z *= f;
}

spmd(L) void div_assign(vec3 varying(L)& res, float varying(L) f) {
    res.x /= f;
    res.y /= f;
    res.z /= f;
}

// other

float uniform_dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

spmd(L) float varying(L) dot(const vec3 varying(L)& a, const vec3 varying(L)& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

spmd(L) void cross(vec3 varying(L)& res, const vec3 varying(L)& v, const vec3 varying(L)& w) {
    res.x = v.y * w.z - v.z * w.y;
    res.y = v.z * w.x - v.x * w.z;
    res.z = v.x * w.y - v.y * w.x;
}

spmd(L) void normalize(vec3 varying(L)& v) {
    div_assign(v, sqrt(dot(v, v)));
}

spmd(L) void splat(vec3 varying(L)& res, const vec3& u) {
    res.x = u.x;
    res.y = u.y;
    res.z = u.z;
}

#if 0
spmd(L) void fma(vec3 varying(L)& res, float varying(L) a, const vec3 varying(L)& b, const vec3 varying(L)& c) {
    res.x = fma(a, b.x, c.x);
    res.y = fma(a, b.y, c.y);
    res.z = fma(a, b.z, c.z);
}
#endif

}

#endif
