#include "sierra/ostream.h"

#define L 4
#include "sierra/math.h"

#include <iostream>

using namespace sierra;

int main() {
    float varying(4) a = {0, 1,  2,  3};
    float varying(4) b = {4, 5,  6,  7};
    float varying(4) c = {8, 9, 10, 11};
    std::cout << exp(a) << std::endl;
    std::cout << log(a) << std::endl;
    std::cout << log2(a) << std::endl;
    std::cout << log10(a) << std::endl;
    std::cout << sin(a) << std::endl;
    std::cout << cos(a) << std::endl;
    std::cout << fma(a, b, c) << std::endl;
}
