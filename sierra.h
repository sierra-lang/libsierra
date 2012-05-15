#ifndef SIERRA_H
#define SIERRA_H

#define spmd(n) __attribute__((sierra_spmd(n)))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector(n)))

namespace sierra {

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

} // namespace sierra

#endif // SIERRA_H

