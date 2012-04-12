#include <type_traits>

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
};

typedef vec3_t<varying, 1> vec3;
typedef vec3_t<varying, 4> vec3_4;
typedef vec3_t<varying, 8> vec3_8;

// ------

void test() {

}

using sierra::vec;

vec<int, 4> imad(vec<int, 4> a, vec<int, 4> b, vec<int, 4> c) {
    return a * b + c;
}

vec<short, 8> smad(vec<short, 8> a, vec<short, 8> b, vec<short, 8> c) {
    vec<bool, 8> mask = true;

    if (mask) {
    }

    return a * b + c;
}
