#include "sierra/defines.h"

spmd(4)
//bool varying(4) test(int uniform a, int varying(4) b) {
bool varying(4) test(int varying(4) a, int varying(4) b) {
    return a < b;
}

#if 0
spmd(8)
//bool varying(8) test(int uniform a, int varying(8) b) {
bool varying(8) test(int varying(8) a, int varying(8) b) {
    return a < b;
}

//spmd(8)
//bool varying(8) test(int uniform a, int varying(8) b) {
bool test(int a, int b) {
    return a < b;
}
#endif

