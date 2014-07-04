/*
 * Copyright (c) 2010-2011, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 */

#include <stdint.h>

#ifdef WIN32
#include <windows.h>
#define rdtsc __rdtsc
#else
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    __inline__ uint64_t rdtsc() {
        uint32_t low, high;
        __asm__ __volatile__ (
            "xorl %%eax,%%eax \n    cpuid"
            ::: "%rax", "%rbx", "%rcx", "%rdx" );
        __asm__ __volatile__ (
                              "rdtsc" : "=a" (low), "=d" (high));
        return (uint64_t)high << 32 | low;
    }
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif            
            
static uint64_t start, end;

static inline void reset_and_start_timer()
{
    start = rdtsc();
}

/* Returns the number of millions of elapsed processor cycles since the
   last reset_and_start_timer() call. */
static inline double get_elapsed_mcycles()
{
    end = rdtsc();
    return (end-start) / (1024. * 1024.);
}
