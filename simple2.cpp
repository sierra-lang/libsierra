#define spmd(n) __attribute__((sierra_spmd((n))))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector((n))))

spmd(4)
float varying(4) test(float uniform a, float uniform b) {
    return a + b;
}

spmd(4)
float varying(4) test(float varying(4) a, float uniform b) {
    return a + b;
}

spmd(4)
float varying(4) test(float uniform a, float varying(4) b) {
    return a + b;
}

spmd(4)
float varying(4) test(float varying(4) a, float varying(4) b) {
    return a + b;
}
