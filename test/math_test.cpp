#include "sierra/ostream.h"

#define L 4
#include "sierra/math.h"

#include <iostream>

using namespace sierra;

int main() {
    float varying(4) a = {0.f, 1.f,  2.f,  3.f};
    float varying(4) b = {4.f, 5.f,  6.f,  7.f};
    float varying(4) c = {8.f, 9.f, 10.f, 11.f};
    std::cout << "exp" << std::endl;
    std::cout << exp(a) << std::endl;
    spmd_mode(L)
        std::cout << fast_exp(a) << std::endl;
    std::cout << "log" << std::endl;
    std::cout << log(a) << std::endl;
    spmd_mode(L)
        std::cout << fast_log(a) << std::endl;
    std::cout << "pow" << std::endl;
    std::cout << pow(a, b) << std::endl;
    spmd_mode(L)
        std::cout << fast_pow(a, b) << std::endl;
    std::cout << log2(a) << std::endl;
    std::cout << log10(a) << std::endl;
    std::cout << sin(a) << std::endl;
    std::cout << cos(a) << std::endl;
    std::cout << fma(a, b, c) << std::endl;
}
