#define spmd(n) __attribute__((sierra_spmd(n)))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector(n)))

spmd(4)
void foo(float varying(4) f) {
    float varying(4) g = f;
}
