#define spmd(n) __attribute__((sierra_spmd((n))))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector((n))))

spmd(4)
int varying(4) test(int uniform a, int varying(4) b) {
    return test(a, b);
}


#if 0
spmd(1)
int varying(4) f(float varying(4) c) {
    uniform int a = 23;
    uniform int b = 42;

    //varying(4) int res = test(a, b);
    varying(4) int asdf;

    //if (a < b) {}
        if (asdf < asdf) {}

    return asdf;
}
#endif

//spmd(4)
//short varying(8) test(int uniform a, unsigned varying(8) b) {
    //return a + b;
//}

//spmd(4)
//float varying(4) test(float uniform a, float uniform b) {
    //return a + b;
//}

//spmd(4)
//float varying(4) test(float varying(4) a, float uniform b) {
    //return a + b;
//}

//spmd(4)
//float varying(4) test(float uniform a, double varying(4) b) {
    //float varying(4) res = a + b;
    //return res;
//}

//float test(float uniform a, double  b) {
    //float res = a + b;
    //return res;
//}

//spmd(4)
//double varying(4) test(short uniform a, long long varying(4) b) {
    //float varying(4) res = a + b;
    //return res;
//}

//spmd(4)
//double varying(4) test(float a) {
    //double varying(4) res = a;
    //return res;
//}
