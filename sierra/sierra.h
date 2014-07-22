/*
 * Copyright (c) 2013-2014, Saarland University
 */

#ifndef SIERRA_H
#define SIERRA_H

#include <cstdlib>
#include <new>
#include "defines.h"

#ifdef _MSC_VER
#include <malloc.h>
#endif

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

#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600)
void* aligned_malloc(size_t size, size_t alignment) { return ::aligned_alloc(alignment, size); }
#elif defined _MSC_VER
void* aligned_malloc(size_t size, size_t alignment) { return ::_aligned_malloc(size, alignment); }
#else
#error "don't know how to retrieve aligned memory"
#endif

}

/*
 * global new/delete overloads in order to get aligned memory
 */

// bad_alloc variants

void* operator new  (std::size_t size) throw(std::bad_alloc) {
    if (void* p = sierra::aligned_malloc(size, 32))
        return p;
    throw std::bad_alloc();
}

void* operator new[](std::size_t size) throw(std::bad_alloc) {
    if (void* p = sierra::aligned_malloc(size, 32))
        return p;
    throw std::bad_alloc();
}

void  operator delete  (void* ptr) throw() { free(ptr); }
void  operator delete[](void* ptr) throw() { free(ptr); }

// nothrow variants

void* operator new  (std::size_t size, const std::nothrow_t&) throw() { return sierra::aligned_malloc(size, 32); }
void* operator new[](std::size_t size, const std::nothrow_t&) throw() { return sierra::aligned_malloc(size, 32); }

void  operator delete  (void* ptr, const std::nothrow_t&) throw() { free(ptr); }
void  operator delete[](void* ptr, const std::nothrow_t&) throw() { free(ptr); }

#endif
