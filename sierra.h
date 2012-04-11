#ifndef SIERRA_H
#define SIERRA_H

#define SIERRA        template<template<class> class DO >
#define SIERRA_FLOAT  typename DO<float>::type
#define SIERRA_DOUBLE typename DO<double>::type
#define SIERRA_INT    typename DO<int>::type

namespace sierra {

// transforms to pointer
template<class T> struct soa { typedef T* type; };

// transforms to vector
template<int L> 
struct vary { 
    template<class T>
    struct ing {
        //typedef number<T, L> type;
        typedef T type __attribute__ ((ext_vector_type(L)));
    };
};

// uniform specialization
template<> 
struct vary<1> { 
    template<class T>
    struct ing {
        typedef T type;
    };
};

//------------------------------------------------------------------------

template<class T> using uniform   = vary< 1>::ing<T>;
template<class T> using varying2  = vary< 2>::ing<T>;
template<class T> using varying4  = vary< 4>::ing<T>;
template<class T> using varying8  = vary< 8>::ing<T>;
template<class T> using varying16 = vary<16>::ing<T>;
template<class T> using varying32 = vary<32>::ing<T>;

//------------------------------------------------------------------------

//template<class T, class U> struct compatible { typedef int type; };

//template<class T>
//struct compatible<T, T> { typedef T type; };

//template<class T, int N>
//struct compatible<T<uniform>, T<vary<N>::ing>> { 
    //typedef typename vary<4>::ing<U>::type type;
//};

//template<template<template <class> class> class T>
//struct compatible<T<uniform>, T<vary<4>::ing>> { 
    //typedef T<vary<4>::ing> type;
//};

//template<template<template <class> class> class T>
//struct compatible<T<vary<4>::ing>, T<uniform>> { 
    //typedef T<vary<4>::ing> type;
//};

template<int i, int j>
struct max {
    static const int value = (i > j) ? i : j;
};

//------------------------------------------------------------------------

} // namespace sierra

#endif // SIERRA_H
