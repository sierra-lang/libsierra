//#include "../sierra.h"

template<int L>
int __attribute__((sierra_vector(L))) foo(int __attribute__((sierra_vector(L))) i) {
    int j = 1;
    int width = 1;
    int __attribute__((sierra_vector(L))) index = j * width + i;
    return index;
}

int main() {
    //int a = foo<1>(42);
    foo<1>(42);
    foo<8>(42);
}
