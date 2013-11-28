#ifndef SIERRA_MATh_H
#define SIERRA_MATh_H

#include "defines.h"

namespace sierra {

#define floatbits(i) *(float varying(L)*) (&i)

static float varying(L) exp(float varying(L));
static float varying(L) exp2(float varying(L));
static float varying(L) log(float varying(L));
static float varying(L) log2(float varying(L));
static float varying(L) log10(float varying(L));
static float varying(L) pow(float varying(L), float varying(L));
static float varying(L) powi(float varying(L), int varying(L));
float varying(L) sqrt(float varying(L)) { return 0.f; }
static float varying(L) sin(float varying(L));
static float varying(L) cos(float varying(L));
static float varying(L) fma(float varying(L), float varying(L), float varying(L)); // fused mutpliy-add
static float varying(L) fabs(float varying(L));
static float varying(L) floor(float varying(L));
static float varying(L) ceil(float varying(L));
static float varying(L) trunc(float varying(L));
static float varying(L) rint(float varying(L));
static float varying(L) nearbyint(float varying(L));

spmd(L)
inline float varying(L) fast_sin(float varying(L) x_full) {
    static const float pi_over_two_vec = 1.57079637050628662109375;
    static const float two_over_pi_vec = 0.636619746685028076171875;
    float varying(L) scaled = x_full * two_over_pi_vec;
    float varying(L) k_real = floor(scaled);
    int varying(L) k = (int varying(L))k_real;

    // Reduced range version of x
    float varying(L) x = x_full - k_real * pi_over_two_vec;
    int varying(L) k_mod4 = k & 3;
    bool varying(L) sin_usecos = (k_mod4 == 1 || k_mod4 == 3);
    bool varying(L) flip_sign = (k_mod4 > 1);

    // These coefficients are from sollya with fpminimax(sin(x)/x, [|0, 2,
    // 4, 6, 8, 10|], [|single...|], [0;Pi/2]);
    static const float sin_c2 = -0.16666667163372039794921875;
    static const float sin_c4 = 8.333347737789154052734375e-3;
    static const float sin_c6 = -1.9842604524455964565277099609375e-4;
    static const float sin_c8 = 2.760012648650445044040679931640625e-6;
    static const float sin_c10 = -2.50293279435709337121807038784027099609375e-8;

    static const float cos_c2 = -0.5;
    static const float cos_c4 = 4.166664183139801025390625e-2;
    static const float cos_c6 = -1.388833043165504932403564453125e-3;
    static const float cos_c8 = 2.47562347794882953166961669921875e-5;
    static const float cos_c10 = -2.59630184018533327616751194000244140625e-7;

    float varying(L) outside = sin_usecos ? 1 : x;
    //float varying(L)  c2 = sin_usecos ? cos_c2 : sin_c2;
    //float varying(L)  c4 = sin_usecos ? cos_c4 : sin_c4;
    //float varying(L)  c6 = sin_usecos ? cos_c6 : sin_c6;
    //float varying(L)  c8 = sin_usecos ? cos_c8 : sin_c8;
    //float varying(L) c10 = sin_usecos ? cos_c10 : sin_c10;

    float varying(L)  c2;
    float varying(L)  c4;
    float varying(L)  c6;
    float varying(L)  c8;
    float varying(L) c10;
    if (sin_usecos) {
         c2 = cos_c2;
         c4 = cos_c4;
         c6 = cos_c6;
         c8 = cos_c8;
        c10 = cos_c10;
    } else {
         c2 = sin_c2;
         c4 = sin_c4;
         c6 = sin_c6;
         c8 = sin_c8;
        c10 = sin_c10;
    }

    float varying(L) x2 = x * x;
    float varying(L) formula = x2 * c10 + c8;
    formula = x2 * formula + c6;
    formula = x2 * formula + c4;
    formula = x2 * formula + c2;
    formula = x2 * formula + 1;
    formula *= outside;

    if (flip_sign)
        formula = -formula;

    return formula;
}

spmd(L)
inline float varying(L) fast_cos(float varying(L) x_full) {
    static const float pi_over_two_vec = 1.57079637050628662109375;
    static const float two_over_pi_vec = 0.636619746685028076171875;
    float varying(L) scaled = x_full * two_over_pi_vec;
    float varying(L) k_real = floor(scaled);
    int varying(L) k = (int varying(L)) k_real;

    // Reduced range version of x
    float varying(L) x = x_full - k_real * pi_over_two_vec;

    int varying(L) k_mod4 = k & 3;
    bool varying(L) cos_usecos = (k_mod4 == 0 || k_mod4 == 2);
    bool varying(L) flip_sign = (k_mod4 == 1 || k_mod4 == 2);

    const float sin_c2 = -0.16666667163372039794921875;
    const float sin_c4 = 8.333347737789154052734375e-3;
    const float sin_c6 = -1.9842604524455964565277099609375e-4;
    const float sin_c8 = 2.760012648650445044040679931640625e-6;
    const float sin_c10 = -2.50293279435709337121807038784027099609375e-8;

    const float cos_c2 = -0.5;
    const float cos_c4 = 4.166664183139801025390625e-2;
    const float cos_c6 = -1.388833043165504932403564453125e-3;
    const float cos_c8 = 2.47562347794882953166961669921875e-5;
    const float cos_c10 = -2.59630184018533327616751194000244140625e-7;

    float varying(L) outside;
    float varying(L) c2;
    float varying(L) c4;
    float varying(L) c6;
    float varying(L) c8;
    float varying(L) c10;

    if (cos_usecos) {
        outside = 1.f;
        c2 = cos_c2;
        c4 = cos_c4;
        c6 = cos_c6;
        c8 = cos_c8;
        c10 = cos_c10;
    } else {
        outside = x;
        c2 = sin_c2;
        c4 = sin_c4;
        c6 = sin_c6;
        c8 = sin_c8;
        c10 =  sin_c10;
    }

    float varying(L) x2 = x * x;
    float varying(L) formula = x2 * c10 + c8;
    formula = x2 * formula + c6;
    formula = x2 * formula + c4;
    formula = x2 * formula + c2;
    formula = x2 * formula + 1.;
    formula *= outside;

    //formula = flip_sign ? -formula : formula;
    if (flip_sign)
        formula = -formula;

    return formula;
}

spmd(L)
inline void sincos(float varying(L) x_full, float varying(L)& uniform sin_result, float varying(L)& uniform cos_result) {
    const float pi_over_two_vec = 1.57079637050628662109375;
    const float two_over_pi_vec = 0.636619746685028076171875;
    float varying(L) scaled = x_full * two_over_pi_vec;
    float varying(L) k_real = floor(scaled);
    int varying(L) k = (int varying(L))k_real;

    // Reduced range version of x
    float varying(L) x = x_full - k_real * pi_over_two_vec;
    int varying(L) k_mod4 = k & 3;
    bool varying(L) cos_usecos = (k_mod4 == 0 || k_mod4 == 2);
    bool varying(L) sin_usecos = (k_mod4 == 1 || k_mod4 == 3);
    bool varying(L) sin_flipsign = (k_mod4 > 1);
    bool varying(L) cos_flipsign = (k_mod4 == 1 || k_mod4 == 2);

    const float one_vec = 1.;
    const float sin_c2 = -0.16666667163372039794921875;
    const float sin_c4 = 8.333347737789154052734375e-3;
    const float sin_c6 = -1.9842604524455964565277099609375e-4;
    const float sin_c8 = 2.760012648650445044040679931640625e-6;
    const float sin_c10 = -2.50293279435709337121807038784027099609375e-8;

    const float cos_c2 = -0.5;
    const float cos_c4 = 4.166664183139801025390625e-2;
    const float cos_c6 = -1.388833043165504932403564453125e-3;
    const float cos_c8 = 2.47562347794882953166961669921875e-5;
    const float cos_c10 = -2.59630184018533327616751194000244140625e-7;

    float varying(L) x2 = x * x;

    float varying(L) sin_formula = x2 * sin_c10 + sin_c8;
    float varying(L) cos_formula = x2 * cos_c10 + cos_c8;
    sin_formula = x2 * sin_formula + sin_c6;
    cos_formula = x2 * cos_formula + cos_c6;

    sin_formula = x2 * sin_formula + sin_c4;
    cos_formula = x2 * cos_formula + cos_c4;

    sin_formula = x2 * sin_formula + sin_c2;
    cos_formula = x2 * cos_formula + cos_c2;

    sin_formula = x2 * sin_formula + one_vec;
    cos_formula = x2 * cos_formula + one_vec;

    sin_formula *= x;

    //*sin_result = sin_usecos ? cos_formula : sin_formula;
    //*cos_result = cos_usecos ? cos_formula : sin_formula;

    //*sin_result = sin_flipsign ? -*sin_result : *sin_result;
    //*cos_result = cos_flipsign ? -*cos_result : *cos_result;

    if (sin_usecos)
        sin_result = cos_formula;
    else
        sin_result = sin_formula;

    if (cos_usecos)
        cos_result = cos_formula;
    else
        cos_result = sin_formula;

    if (sin_flipsign)
        sin_result = -sin_result;

    if (cos_flipsign)
        cos_result = -cos_result;
}

spmd(L)
inline float varying(L) fast_exp(float varying(L) x_full) {
    static const float ln2_part1 = 0.6931457519;
    static const float ln2_part2 = 1.4286067653e-6;
    static const float one_over_ln2 = 1.44269502162933349609375;

    float varying(L) scaled = x_full * one_over_ln2;
    float varying(L) k_real = floor(scaled);
    int varying(L) k = (int varying(L)) k_real;

    // Reduced range version of x
    float varying(L) x = x_full - k_real * ln2_part1;
    x -= k_real * ln2_part2;

    // These coefficients are for e^x in [0, ln(2)]
    static const float one = 1.;
    static const float c2 = 0.4999999105930328369140625;
    static const float c3 = 0.166668415069580078125;
    static const float c4 = 4.16539050638675689697265625e-2;
    static const float c5 = 8.378830738365650177001953125e-3;
    static const float c6 = 1.304379315115511417388916015625e-3;
    static const float c7 = 2.7555381529964506626129150390625e-4;

    float varying(L) result = x * c7 + c6;
    result = x * result + c5;
    result = x * result + c4;
    result = x * result + c3;
    result = x * result + c2;
    result = x * result + one;
    result = x * result + one;

    // Compute 2^k (should differ for float and double, but I'll avoid
    // it for now and just do floats)
    const int fpbias = 127;
    int varying(L) biased_n = k + fpbias;
    bool varying(L) overflow = k > fpbias;
    // Minimum exponent is -126, so if k is <= -127 (k + 127 <= 0)
    // we've got underflow. -127 * ln(2) -> -88.02. So the most
    // negative float input that doesn't result in zero is like -88.
    bool varying(L) underflow = (biased_n <= 0);
    static const int InfBits = 0x7f800000;
    biased_n <<= 23;
    // Reinterpret this thing as float
    float varying(L) two_to_the_n = floatbits(biased_n);
    // Handle both doubles and floats (hopefully eliding the copy for float)
    float varying(L) elemtype_2n = two_to_the_n;
    result *= elemtype_2n;

    //result = overflow ? floatbits(InfBits) : result;
    if (overflow)
        result = floatbits(InfBits);

    //result = underflow ? 0. : result;
    if (underflow)
        result = 0.f;

    return result;
}

}

#endif
