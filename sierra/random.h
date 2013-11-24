#ifndef SIERRA_RANDOM_H
#define SIERRA_RANDOM_H

#include "defines.h"

namespace sierra {

struct RNGState {
    unsigned z1, z2, z3, z4;
};

spmd(L)
unsigned varying(L) random(RNGState varying(L)& state) {
    unsigned varying(L) b;
    b  = ((state.z1 << 6) ^ state.z1) >> 13;
    state.z1 = ((state.z1 & 4294967294U) << 18) ^ b;
    b  = ((state.z2 << 2) ^ state.z2) >> 27; 
    state.z2 = ((state.z2 & 4294967288U) << 2) ^ b;
    b  = ((state.z3 << 13) ^ state.z3) >> 21;
    state.z3 = ((state.z3 & 4294967280U) << 7) ^ b;
    b  = ((state.z4 << 3) ^ state.z4) >> 12;
    state.z4 = ((state.z4 & 4294967168U) << 13) ^ b;
    return (state.z1 ^ state.z2 ^ state.z3 ^ state.z4);
}

unsigned uniform random(RNGState uniform& state) {
    unsigned uniform b;
    b  = ((state.z1 << 6) ^ state.z1) >> 13;
    state.z1 = ((state.z1 & 4294967294U) << 18) ^ b;
    b  = ((state.z2 << 2) ^ state.z2) >> 27; 
    state.z2 = ((state.z2 & 4294967288U) << 2) ^ b;
    b  = ((state.z3 << 13) ^ state.z3) >> 21;
    state.z3 = ((state.z3 & 4294967280U) << 7) ^ b;
    b  = ((state.z4 << 3) ^ state.z4) >> 12;
    state.z4 = ((state.z4 & 4294967168U) << 13) ^ b;
    return (state.z1 ^ state.z2 ^ state.z3 ^ state.z4);
}

spmd(L)
float varying(L) frandom(RNGState varying(L)& state) {
    unsigned varying(L) irand = random(state);
    irand &= (1ul<<23)-1;
    return floatbits(0x3F800000 | irand)-1.0f;
}

float uniform frandom(RNGState uniform& uniform state) {
    unsigned uniform irand = random(state);
    irand &= (1ul<<23)-1;
    return floatbits(0x3F800000 | irand)-1.0f;
}

spmd(L)
void seed_rng(RNGState varying(L)& state, unsigned seed) {
    state.z1 = seed;
    state.z2 = seed ^ 0xbeeff00d;
    state.z3 = ((seed & 0xfffful) << 16) | (seed >> 16);
    state.z4 = (((seed & 0xfful) << 24) | ((seed & 0xff00ul)  << 8) |
                 ((seed & 0xff0000ul) >> 8) | (seed & 0xff000000ul) >> 24);
}

void seed_rng(RNGState uniform& state, uniform unsigned seed) {
    state.z1 = seed;
    state.z2 = seed ^ 0xbeeff00d;
    state.z3 = ((seed & 0xfffful) << 16) | (seed >> 16);
    state.z4 = (((seed & 0xfful) << 24) | ((seed & 0xff00ul)  << 8) |
                 ((seed & 0xff0000ul) >> 8) | (seed & 0xff000000ul) >> 24);
}

}

#endif