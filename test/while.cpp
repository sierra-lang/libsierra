#define spmd(n) __attribute__((sierra_spmd((n))))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector((n))))


#define L 4

spmd(L)
float varying(L) foo(float varying(L) a, float varying(L) b) {
    while (a < b) {
        a *= b;
    }

    return a;
}
