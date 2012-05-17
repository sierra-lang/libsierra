#ifndef SIERRA_OSTREAM_H
#define SIERRA_OSTREAM_H

#include <ostream>

#include "sierra.h"

template<class T, int L>
std::ostream& operator << (std::ostream& o, T varying(L) vec) {
    o << '(';
    for (int i = 0; i < L-1; ++i)
        o << sierra::extract(vec, i) << ", ";

    o << sierra::extract(vec, L-1) << ')';

    return o;
}


#endif // SIERRA_OSTREAM_H
