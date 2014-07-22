/*
 * Copyright (c) 2010-2011, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 */

#ifndef SIERRA_BENCHMARK_H
#define SIERRA_BENCHMARK_H

#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint>

#ifdef WIN32
#include <windows.h>
#define rdtsc __rdtsc
#else
inline uint64_t rdtsc() {
    uint32_t low, high;
    __asm__ __volatile__ (
        "xorl %%eax,%%eax \n    cpuid"
        ::: "%rax", "%rbx", "%rcx", "%rdx" );
    __asm__ __volatile__ (
                            "rdtsc" : "=a" (low), "=d" (high));
    return (uint64_t)high << 32 | low;
}
#endif

namespace sierra {

double benchmark(std::function<void()> f, size_t num = 11u) {
    std::vector<double> times(num);
    for (auto& time : times) {
        auto start = rdtsc();
        f();
        auto end = rdtsc();
        time = (end-start) / (1024.*1024.);
    }

    // compute median
    std::sort(times.begin(), times.end());
    return times[times.size()/2];
}

}

#endif
