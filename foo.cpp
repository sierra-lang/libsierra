typedef bool  bxmm __attribute__ ((vector_size(16)));
typedef float fxmm __attribute__ ((vector_size(16)));

bxmm f(fxmm a, fxmm b) {
    return a < b;
}
