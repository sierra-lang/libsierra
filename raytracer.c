#define VEC3(L) \
    typedef struct { float vector[L] x, y, z; } vec3_ ## L;

VEC3(1)
VEC3(4)
typedef vec3_1 vec3;

#define ADD(RES, SPMD, A, B) \
    spmd[SPMD] vec3_ ## RES add_ ## SPMD ## _ ## A ## _ ## B (vec3_ ## A a, vec3_ ## B b) { \
        vec3_ ## RES res; \
        res.x = a.x + b.x; \
        res.y = a.y + b.y; \
        res.z = a.z + b.z; \
        return res; \
    }

ADD(1, 1, 1, 1)
ADD(4, 1, 1, 4)
ADD(4, 1, 4, 1)
ADD(4, 1, 4, 4)
ADD(1, 4, 1, 1)
ADD(4, 4, 1, 4)
ADD(4, 4, 4, 1)
ADD(4, 4, 4, 4)
