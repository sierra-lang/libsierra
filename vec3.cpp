// compile with
// clang++ vec3.cpp -std=c++11 -c -O2 -o - -S

namespace sierra {

/*
 * primitive vector types
 */

// _sierra_vec<Type, Length>
template<class T, int L> 
struct internal_vec       
{ 
    typedef T __attribute__((ext_vector_type(L))) type; 
};

// uniform specialization
template<class T>        
struct internal_vec<T, 1> 
{ 
    typedef T type; 
};

// alias for convenience
template<class T, int L> 
using vec = typename internal_vec<T, L>::type;

/*
 * varying SoF transformation
 */

// transforms to vector
template<class T, int L> 
struct varying { 
    typedef vec<T, L> type;
};


} // namespace sierra


//------------------------------------------------------------------------------


using sierra::vec;
using sierra::varying;


template<template <class, int> class T, int L >
struct vec3_t {
    typename T<float, L>::type x, y, z;

    template<class U>
    vec3_t operator + (U v) const {
        vec3_t res;
        res.x = x + v.x;
        res.y = y + v.y;
        res.z = z + v.z;
        return res;
    }
};

typedef vec3_t<varying, 1> vec3;
typedef vec3_t<varying, 4> vec3_4;
typedef vec3_t<varying, 8> vec3_8;

// test
vec3   test_add_1_1(const vec3&   a, const vec3&   b) { return a + b; }
// this is broken because of wrong vector length for 'vec3_t res'
//vec3_4 test_add_1_4(const vec3&   a, const vec3_4& b) { return a + b; }
vec3_4 test_add_4_1(const vec3_4& a, const vec3&   b) { return a + b; }
vec3_4 test_add_4_4(const vec3_4& a, const vec3_4& b) { return a + b; }
