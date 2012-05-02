#define spmd(n) __attribute__((sierra_spmd((n))))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector((n))))

spmd(256)
int varying(8) test(short uniform a, double varying(2) b) {
    int varying(8) i = a;
    return i;
    //return a + b;
}

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
