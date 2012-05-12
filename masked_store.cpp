#define spmd(n) __attribute__((sierra_spmd((n))))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector((n))))

#define L 8

float varying(L) g_float_vector;
float varying(L) h_float_vector;

spmd(L)
void test(float varying(L) v, float varying(L) w) {
    if (v < w)
        g_float_vector = v;
    else
        h_float_vector = w;
}
