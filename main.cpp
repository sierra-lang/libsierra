#include <type_traits>

// _vec<Type, Length>
template<class T, int L> using _vec = T __attribute__((ext_vector_type(L)));

// transforms to pointer
//template<class T> struct soa { typedef T* type; };


// transforms to vector
template<class T, int L, int... M> 
struct varying { 
    typedef _vec<T, L> type __attribute__ ((ext_vector_type(L)));
};

// uniform specialization
//template<> 
//struct vary<1> { 
    //template<class T>
    //struct ing {
        //typedef T type;
    //};
//};

template<template <class, int, int...> class T, int L, int... M>
struct vec3_t {
    typename T<float, L, M>::type x, y, z;
};

typedef vec3_t<varying, 4, 8> vec3_4;
typedef vec3_t<varying, 4, 8> vec3_4;

// ------

void test() {

}

_vec<float, 4> fmad(_vec<float, 4> a, _vec<float, 4> b, _vec<float, 4> c) {
    return a * b + c;
}

