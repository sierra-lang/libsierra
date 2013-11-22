#ifndef SIERRA_H
#define SIERRA_H

#include <stdint.h>

#define spmd(n) __attribute__((sierra_spmd(n)))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector(n)))
#define program_index(n) seq<n>()

#define spmd_mode(L) if ((bool varying(L)) true)

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

} // namespace sierra

#endif // SIERRA_H

