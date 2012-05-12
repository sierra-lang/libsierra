#define spmd(n) __attribute__((sierra_spmd((n))))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector((n))))


spmd(4)
float varying(4) foo(float varying(4) a, float varying(4) b) {
    while (a < b)
        a *= b;

    return a;
}
