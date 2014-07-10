/*
 * Copyright (c) 2013-2014, Saarland University
 */

#ifndef SIERRA_H
#define SIERRA_H

#include <stdint.h>
//#include <cstdlib>
#include "defines.h"

namespace sierra {

template<class T>
inline T nextpow2(T val) {
    val |= (val >> 1);
    val |= (val >> 2);
    val |= (val >> 4);
    val |= (val >> 8);
    val |= (val >> 16);
    //val |= (val >> 32);
    return val + 1;
}

template<class T, int L>
T extract(T varying(L) vec, int i) {
    T* p = (T*) &vec;
    return p[i];
}

template<class T, int L>
void insert(T varying(L)& vec, int i, T val) {
    T* p = (T*) &vec;
    p[i] = val;
}

/*
 * make scalars behave as vectors
 */

template<class T>
T extract(T scalar, int) {
    return scalar;
}

template<class T>
void insert(T& scalar, int i, T val) {
    scalar = val;
}

template<int L>
int varying(L) seq() {
    int varying(L) res;
    for (int i = 0; i < L; ++i)
        insert(res, i, i);
    return res;
}

template<int step, class B>
void for_each(int begin, int end, B body) {
    int i = begin;

    if (i % step != 0) {
        i = nextpow2(i);
        if (i - step + seq<step>() >= begin)
            body();
    }

    while (i < end) {
        body();
        i += step;
    }

    if (end % step != 0)
        if (i - step + seq<step>() < end )
            body();
}

template<int> struct Tile {};

template<>
struct Tile<1> {
    static int const x = 1;
    static int const y = 1;
};

template<>
struct Tile<2> {
    static int const x = 2;
    static int const y = 1;
};

template<>
struct Tile<4> {
    static int const x = 2;
    static int const y = 2;
};

template<>
struct Tile<8> {
    static int const x = 4;
    static int const y = 2;
};

template<>
struct Tile<16> {
    static int const x = 4;
    static int const y = 4;
};

}

/*
 * global new/delete overloads in order to get aligned memory
 */

// bad_alloc variants

void* operator new  (std::size_t size) throw(std::bad_alloc) {
    void* p;
    posix_memalign(&p, 32, size);
    if (p)
        return p;
    throw std::bad_alloc();
}

void* operator new[](std::size_t size) throw(std::bad_alloc) {
    void* p;
    posix_memalign(&p, 32, size);
    if (p)
        return p;
    throw std::bad_alloc();
}

void  operator delete  (void* ptr) throw() { free(ptr); }
void  operator delete[](void* ptr) throw() { free(ptr); }

// nothrow variants

void* operator new  (std::size_t size, const std::nothrow_t&) throw() {
    void* p;
    posix_memalign(&p, 32, size);
    return p;
}

void* operator new[](std::size_t size, const std::nothrow_t&) throw() {
    void* p;
    posix_memalign(&p, 32, size);
    return p;
}

void  operator delete  (void* ptr, const std::nothrow_t&) throw() { free(ptr); }
void  operator delete[](void* ptr, const std::nothrow_t&) throw() { free(ptr); }

#endif
