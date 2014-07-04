/*
 * Copyright (c) 2010-2012, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 */

#define NOMINMAX

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <algorithm>

//#include "options_defs.h"
#include "sierra/timing.h"

void black_scholes_sierra(float Sa[], float Xa[], float Ta[], float ra[], float va[], float result[], int count);
void binomial_put_sierra (float Sa[], float Xa[], float Ta[], float ra[], float va[], float result[], int count);

static void usage() {
    printf("usage: options [--count=<num options>]\n");
}


int main(int argc, char *argv[]) {
    //int nOptions = 128*1024;
    int nOptions = 1024*1024;

    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "--count=", 8) == 0) {
            nOptions = atoi(argv[i] + 8);
            if (nOptions <= 0) {
                usage();
                exit(1);
            }
        }
    }

    //float *S = new float[nOptions];
    //float *X = new float[nOptions];
    //float *T = new float[nOptions];
    //float *r = new float[nOptions];
    //float *v = new float[nOptions];
    //float *result = new float[nOptions];

    float *S;
    float *X;
    float *T;
    float *r;
    float *v;
    float *result;

    posix_memalign((void**) &S, 32, sizeof(float)*nOptions);
    posix_memalign((void**) &X, 32, sizeof(float)*nOptions);
    posix_memalign((void**) &T, 32, sizeof(float)*nOptions);
    posix_memalign((void**) &r, 32, sizeof(float)*nOptions);
    posix_memalign((void**) &v, 32, sizeof(float)*nOptions);
    posix_memalign((void**) &result, 32, sizeof(float)*nOptions);

    for (int i = 0; i < nOptions; ++i) {
        S[i] = 100;  // stock price
        X[i] = 98;   // option strike price
        T[i] = 2;    // time (years)
        r[i] = .02;  // risk-free interest rate
        v[i] = 5;    // volatility
    }

    double sum;

#if 0
    //
    // Binomial options pricing model, ispc implementation
    //
    double binomial_sierra = 1e30;
    for (int i = 0; i < 3; ++i) {
        reset_and_start_timer();
        binomial_put_sierra(S, X, T, r, v, result, nOptions);
        double dt = get_elapsed_mcycles();
        sum = 0.;
        for (int i = 0; i < nOptions; ++i)
            sum += result[i];
        binomial_sierra = std::min(binomial_sierra, dt);
    }
    printf("[binomial ispc, 1 thread]:\t[%.3f] million cycles (avg %f)\n", 
           binomial_sierra, sum / nOptions);

    //
    // Binomial options pricing model, ispc implementation, tasks
    //
    double binomial_tasks = 1e30;
    for (int i = 0; i < 3; ++i) {
        reset_and_start_timer();
        binomial_put_ispc_tasks(S, X, T, r, v, result, nOptions);
        double dt = get_elapsed_mcycles();
        sum = 0.;
        for (int i = 0; i < nOptions; ++i)
            sum += result[i];
        binomial_tasks = std::min(binomial_tasks, dt);
    }
    printf("[binomial ispc, tasks]:\t\t[%.3f] million cycles (avg %f)\n", 
           binomial_tasks, sum / nOptions);

    //
    // Binomial options, serial implementation
    //
#endif
    {
        double times[7];
        for (int i = 0; i < 7; ++i) {
            reset_and_start_timer();
            binomial_put_sierra(S, X, T, r, v, result, nOptions);
            times[i] = get_elapsed_mcycles();
            sum = 0.;
            for (int i = 0; i < nOptions; ++i)
                sum += result[i];
            //binomial_sierra = std::min(binomial_sierra, dt);
        }
        //printf("[binomial serial]:\t\t[%.3f] million cycles (avg %f)\n", 
            //binomial_sierra, sum / nOptions);
        std::cout << "binomial" << std::endl;
        std::cout << times[3] << std::endl;
    }

#if 0

    //
    // Black-Scholes options pricing model, ispc implementation, 1 thread
    //
    double bs_ispc = 1e30;
    for (int i = 0; i < 3; ++i) {
        reset_and_start_timer();
        black_scholes_ispc(S, X, T, r, v, result, nOptions);
        double dt = get_elapsed_mcycles();
        sum = 0.;
        for (int i = 0; i < nOptions; ++i)
            sum += result[i];
        bs_ispc = std::min(bs_ispc, dt);
    }
    printf("[black-scholes ispc, 1 thread]:\t[%.3f] million cycles (avg %f)\n", 
           bs_ispc, sum / nOptions);

    //
    // Black-Scholes options pricing model, ispc implementation, tasks
    //
    double bs_ispc_tasks = 1e30;
    for (int i = 0; i < 3; ++i) {
        reset_and_start_timer();
        black_scholes_ispc_tasks(S, X, T, r, v, result, nOptions);
        double dt = get_elapsed_mcycles();
        sum = 0.;
        for (int i = 0; i < nOptions; ++i)
            sum += result[i];
        bs_ispc_tasks = std::min(bs_ispc_tasks, dt);
    }
    printf("[black-scholes ispc, tasks]:\t[%.3f] million cycles (avg %f)\n", 
           bs_ispc_tasks, sum / nOptions);

    //
    // Black-Scholes options pricing model, serial implementation
    //
#endif
    {
    double times[7];
    for (int i = 0; i < 7; ++i) {
        reset_and_start_timer();
        black_scholes_sierra(S, X, T, r, v, result, nOptions);
        times[i] = get_elapsed_mcycles();
        sum = 0.;
        for (int i = 0; i < nOptions; ++i)
            sum += result[i];
        //bs_sierra = std::min(bs_sierra, dt);
    }
    std::sort(times, times + 7);
    //printf("[black-scholes serial]:\t\t[%.3f] million cycles (avg %f)\n", bs_sierra, 
           //sum / nOptions);
    std::cout << "black scholes" << std::endl;
    std::cout << times[3] << std::endl; // median
    }

#if 0
    printf("\t\t\t\t(%.2fx speedup from ISPC, %.2fx speedup from ISPC + tasks)\n", 
           bs_serial / bs_ispc, bs_serial / bs_ispc_tasks);

#endif
    return 0;
}
