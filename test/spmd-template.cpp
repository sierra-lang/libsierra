#include "sierra/defines.h"

template<int L>
spmd(L) float varying(L) foo(float varying(L) f) {
    return f;
}

int main() {
    spmd_mode(4)
        foo((float varying(4)){0, 1, 2, 3});
}
