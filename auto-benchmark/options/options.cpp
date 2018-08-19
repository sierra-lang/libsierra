/*
 * Copyright (c) 2010-2012, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 */

#define NOMINMAX

#include <cmath>
#include <iostream>

#include "sierra/benchmark.h"
#include "sierra/sierra.h"

#define L LENGTH
//#include "sierra/math.h"

#define BINOMIAL_NUM 64

using namespace sierra;

// cumulative normal distribution function
static float CND(float X) {
    float w;
    spmd_mode(L) {
        auto l  = fabs(X);
        auto k  = 1.0f / (1.0f + 0.2316419f * l);
        auto k2 = k*k;
        auto k3 = k2*k;
        auto k4 = k2*k2;
        auto k5 = k3*k2;

        static const float invSqrt2Pi = 0.39894228040f;
        w = (0.31938153f * k - 0.356563782f * k2 + 1.781477937f * k3 + -1.821255978f * k4 + 1.330274429f * k5);
        w *= invSqrt2Pi * exp(-l * l * .5f);

        if (X > 0.f)
            w = 1.0f - w;
    }
    return w;
}

static float binomial(float S, float X, float T, float r, float v) {
    float V[BINOMIAL_NUM];

    float dt = T / BINOMIAL_NUM;
    //float varying(L) u = exp(v * sqrt(dt));
    float u = exp(v * sqrt(dt));
    float d = 1. / u;
    float disc = exp(r * dt);
    float Pu = (disc - d) / (u - d);

    for (int j = 0; j < BINOMIAL_NUM; ++j) {
        float upow= pow(u, (float )(2*j-BINOMIAL_NUM));

        float tmp1 = 0.0f;
        float tmp2 = X - S * upow;
        V[j] = (tmp1 > tmp2 ? tmp1 : tmp2);
    }

    for (int j = BINOMIAL_NUM-1; j >= 0; --j)
        for (int k = 0; k < j; ++k)
            V[k] = ((1 - Pu) * V[k] + Pu * V[k + 1]) / disc;
    return V[0];
}

static void binomial_put(float Sa[], float Xa[], float Ta[], float ra[], float va[], float result[], int count) {
    auto pS = (float varying(L)*) Sa;
    auto pX = (float varying(L)*) Xa;
    auto pT = (float varying(L)*) Ta;
    auto pr = (float varying(L)*) ra;
    auto pv = (float varying(L)*) va;
    auto pres = (float varying(L)*) result;
    for (int ii = 0; ii < count; ii += L) {
        auto S = *(pS++);
        auto X = *(pX++);
        auto T = *(pT++);
        auto r = *(pr++);
        auto v = *(pv++);
        *(pres++) = binomial(S, X, T, r, v);
    }
}

static void black_scholes(float Sa[], float Xa[], float Ta[], float ra[], float va[], float result[], int count) {
    auto pS = (float varying(L)*) Sa;
    auto pX = (float varying(L)*) Xa;
    auto pT = (float varying(L)*) Ta;
    auto pr = (float varying(L)*) ra;
    auto pv = (float varying(L)*) va;
    auto pres = (float varying(L)*) result;
    for (int ii = 0; ii < count; ii += L) {
        auto S = *(pS++);
        auto X = *(pX++);
        auto T = *(pT++);
        auto r = *(pr++);
        auto v = *(pv++);

        float varying(L) sqrtT;
        spmd_mode(L)
            sqrtT = sqrt(T);
        auto d1 = ( + (r + v * v * .5f) * T) / (v * sqrtT);
        auto d2 = d1 - v * sqrtT;
        float varying(L) e;
        spmd_mode(L) {
            auto arg = -r * T;
            e = exp(arg);
        }
        *(pres++) = S * CND(d1) - X * e * CND(d2);
    }
}

int main(int argc, char *argv[]) {
    int num_iters = 1;
    if (argc == 2) {
        num_iters = atoi(argv[1]);
    } else if (argc != 1) {
        const char* exe = argc > 0 ? argv[0] : "options";
        std::cout << "usage: " << exe << " [number of iterations]" << std::endl;
        return EXIT_FAILURE;
    }

    int num = 1024*1024;
    auto S = new float[num];
    auto X = new float[num];
    auto T = new float[num];
    auto r = new float[num];
    auto v = new float[num];
    auto result = new float[num];

    for (int i = 0; i < num; ++i) {
        S[i] = 100.00f; // stock price
        X[i] =  98.00f; // option strike price
        T[i] =   2.00f; // time (years)
        r[i] =   0.02f; // risk-free interest rate
        v[i] =   5.00f; // volatility
    }

    std::cout << "binomial: " << std::endl;
    benchmark([&] { binomial_put (S, X, T, r, v, result, num); }, num_iters);
    std::cout << "black scholes: " << std::endl;
    benchmark([&] { black_scholes(S, X, T, r, v, result, num); }, num_iters);

    delete[] S;
    delete[] X;
    delete[] T;
    delete[] r;
    delete[] v;
    delete[] result;
}
