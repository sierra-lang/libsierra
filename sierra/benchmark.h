/*
 * Copyright (c) 2010-2011, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 */

#ifndef SIERRA_BENCHMARK_H
#define SIERRA_BENCHMARK_H

#include <algorithm>
#include <functional>
#include <iostream>
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

void benchmark(std::function<void()> f, size_t num_iters) {
    std::vector<double> times(num_iters);
    for (auto& time : times) {
        auto start = rdtsc();
        f();
        auto end = rdtsc();
        time = (end-start) / (1024.*1024.);
    }

    // compute median
    std::sort(times.begin(), times.end());
    std::cout << "median of " << num_iters << " runs: " << times[num_iters/2] << "ms" << std::endl;
}

}

#endif
