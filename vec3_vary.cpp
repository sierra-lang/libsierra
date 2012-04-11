#include "sierra.h"

using namespace sierra;

SIERRA struct vec3_t {
    SIERRA_FLOAT x, y, z;

    vec3_t() {}

    template<class T>
    vec3_t(T x, T y, T z) 
        : x(x)
        , y(y)
        , z(z)
    {}

    template<class U>
    vec3_t operator + (U v) const {
        vec3_t res;
        res.x = x + v.x;
        res.y = y + v.y;
        res.z = z + v.z;
        return res;
    }
};

typedef vec3_t<uniform> vec3;
typedef vec3_t<varying4> vec3_4;
typedef vec3_t<varying8> vec3_8;


// test
vec3   test_add_1_1(const vec3&   a, const vec3&   b) { return a + b; }
//vec3_4 test_add_1_4(const vec3&   a, const vec3_4& b) { return a + b; }
vec3_4 test_add_4_1(const vec3_4& a, const vec3&   b) { return a + b; }
vec3_4 test_add_4_4(const vec3_4& a, const vec3_4& b) { return a + b; }
