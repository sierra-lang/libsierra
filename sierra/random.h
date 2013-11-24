#ifndef SIERRA_RANDOM_H
#define SIERRA_RANDOM_H

namespace sierra {

struct RNGState {
    unsigned int z1, z2, z3, z4;
};

unsigned int random(varying RNGState * uniform state)
{
    unsigned int b;

    b  = ((state->z1 << 6) ^ state->z1) >> 13;
    state->z1 = ((state->z1 & 4294967294U) << 18) ^ b;
    b  = ((state->z2 << 2) ^ state->z2) >> 27; 
    state->z2 = ((state->z2 & 4294967288U) << 2) ^ b;
    b  = ((state->z3 << 13) ^ state->z3) >> 21;
    state->z3 = ((state->z3 & 4294967280U) << 7) ^ b;
    b  = ((state->z4 << 3) ^ state->z4) >> 12;
    state->z4 = ((state->z4 & 4294967168U) << 13) ^ b;
    return (state->z1 ^ state->z2 ^ state->z3 ^ state->z4);
}

inline uniform unsigned int random(uniform RNGState * uniform state)
{
    uniform unsigned int b;

    b  = ((state->z1 << 6) ^ state->z1) >> 13;
    state->z1 = ((state->z1 & 4294967294U) << 18) ^ b;
    b  = ((state->z2 << 2) ^ state->z2) >> 27; 
    state->z2 = ((state->z2 & 4294967288U) << 2) ^ b;
    b  = ((state->z3 << 13) ^ state->z3) >> 21;
    state->z3 = ((state->z3 & 4294967280U) << 7) ^ b;
    b  = ((state->z4 << 3) ^ state->z4) >> 12;
    state->z4 = ((state->z4 & 4294967168U) << 13) ^ b;
    return (state->z1 ^ state->z2 ^ state->z3 ^ state->z4);
}

inline float frandom(varying RNGState * uniform state)
{
    unsigned int irand = random(state);
    irand &= (1ul<<23)-1;
    return floatbits(0x3F800000 | irand)-1.0f;
}

inline uniform float frandom(uniform RNGState * uniform state)
{
    uniform unsigned int irand = random(state);
    irand &= (1ul<<23)-1;
    return floatbits(0x3F800000 | irand)-1.0f;
}

inline void seed_rng(varying RNGState * uniform state, 
                            unsigned int seed) {
    state->z1 = seed;
    state->z2 = seed ^ 0xbeeff00d;
    state->z3 = ((seed & 0xfffful) << 16) | (seed >> 16);
    state->z4 = (((seed & 0xfful) << 24) | ((seed & 0xff00ul)  << 8) |
                 ((seed & 0xff0000ul) >> 8) | (seed & 0xff000000ul) >> 24);
}

inline void seed_rng(uniform RNGState * uniform state, 
                            uniform unsigned int seed) {
    state->z1 = seed;
    state->z2 = seed ^ 0xbeeff00d;
    state->z3 = ((seed & 0xfffful) << 16) | (seed >> 16);
    state->z4 = (((seed & 0xfful) << 24) | ((seed & 0xff00ul)  << 8) |
                 ((seed & 0xff0000ul) >> 8) | (seed & 0xff000000ul) >> 24);
}

}

#endif
