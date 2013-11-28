// -*- mode: c++ -*-
/*
  Copyright (c) 2010-2011, Intel Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of Intel Corporation nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.


   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
*/

#define BINOMIAL_NUM 64

#include "sierra/sierra.h"

#define L LENGTH
#include "sierra/vec3.h"

using namespace sierra;

// Cumulative normal distribution function
spmd(L)
inline float varying(L) CND(float varying(L) X) {
    float varying(L) l = fabs(X);

    float varying(L) k = 1.0f / (1.0f + 0.2316419f * l);
    float varying(L) k2 = k*k;
    float varying(L) k3 = k2*k;
    float varying(L) k4 = k2*k2;
    float varying(L) k5 = k3*k2;

    static const float invSqrt2Pi = 0.39894228040f;
    float varying(L) w = (0.31938153f * k - 0.356563782f * k2 + 1.781477937f * k3 +
               -1.821255978f * k4 + 1.330274429f * k5);
    w *= invSqrt2Pi * fast_exp(-l * l * .5f);

    if (X > 0.f)
        w = 1.0f - w;
    return w;
}

#if 0
task void
bs_task(uniform float Sa[], uniform float Xa[], uniform float Ta[],
        uniform float ra[], uniform float va[], 
        uniform float result[], uniform int count) {
    uniform int first = taskIndex * (count/taskCount);
    uniform int last = min(count, (int)((taskIndex+1) * (count/taskCount)));

    foreach (i = first ... last) {
        float S = Sa[i], X = Xa[i], T = Ta[i], r = ra[i], v = va[i];

        float d1 = (log(S/X) + (r + v * v * .5f) * T) / (v * sqrt(T));
        float d2 = d1 - v * sqrt(T);

        result[i] = S * CND(d1) - X * exp(-r * T) * CND(d2);
    }
}

export void
black_scholes_ispc_tasks(uniform float Sa[], uniform float Xa[], uniform float Ta[],
                         uniform float ra[], uniform float va[], 
                         uniform float result[], uniform int count) {
    uniform int nTasks = max((int)64, (int)count/16384);
    launch[nTasks] bs_task(Sa, Xa, Ta, ra, va, result, count);
}


export void
black_scholes_ispc(uniform float Sa[], uniform float Xa[], uniform float Ta[],
                   uniform float ra[], uniform float va[], 
                   uniform float result[], uniform int count) {
    foreach (i = 0 ... count) {
        float S = Sa[i], X = Xa[i], T = Ta[i], r = ra[i], v = va[i];

        float d1 = (log(S/X) + (r + v * v * .5f) * T) / (v * sqrt(T));
        float d2 = d1 - v * sqrt(T);

        result[i] = S * CND(d1) - X * exp(-r * T) * CND(d2);
    }
}
#endif

spmd(L)
inline float varying(L) binomial_put(float varying(L) S, float varying(L) X, float varying(L) T, float varying(L) r, float varying(L) v) {
    float varying(L) V[BINOMIAL_NUM];

    float varying(L) dt = T / BINOMIAL_NUM;
    float varying(L) u = fast_exp(v * sqrt(dt));
    float varying(L) d = 1. / u;
    float varying(L) disc = exp(r * dt);
    float varying(L) Pu = (disc - d) / (u - d);

    for (uniform int j = 0; j < BINOMIAL_NUM; ++j) {
        float varying(L) upow = fast_pow(u, (float varying(L))(2*j-BINOMIAL_NUM));
        V[j] = fmax(0., X - S * upow);
    }

    for (uniform int j = BINOMIAL_NUM-1; j >= 0; --j)
        for (uniform int k = 0; k < j; ++k)
            V[k] = ((1 - Pu) * V[k] + Pu * V[k + 1]) / disc;
    return V[0];
}

spmd(L)
void binomial_put_ispc(uniform float Sa[], uniform float Xa[], uniform float Ta[], 
                  uniform float ra[], uniform float va[], 
                  uniform float result[], uniform int count) {
    float varying(L)* pS = (float varying(L)*) Sa;
    float varying(L)* pX = (float varying(L)*) Xa;
    float varying(L)* pT = (float varying(L)*) Ta;
    float varying(L)* pr = (float varying(L)*) ra;
    float varying(L)* pv = (float varying(L)*) va;
    float varying(L)* pres = (float varying(L)*) result;
    for (int ii = 0; ii < count; ii += L) {
        int varying(L) i = ii + seq<L>();
        float varying(L) S = *pS++;
        float varying(L) X = *pX++;
        float varying(L) T = *pT++;
        float varying(L) r = *pr++;
        float varying(L) v = *pv++;
        *pres = binomial_put(S, X, T, r, v);
    }
}

