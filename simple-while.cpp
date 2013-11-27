#include "../sierra.h"

#include <iostream>

int main() {
    int varying(4) i = 0;

    int num_iters = 0;
    while (i < (int varying(4)){ 23, 42, 7, 666 }) {
        i = i + 1;
        ++num_iters;
    }

    std::cout << sierra::extract(i, 0) << std::endl;
    std::cout << sierra::extract(i, 1) << std::endl;
    std::cout << sierra::extract(i, 2) << std::endl;
    std::cout << sierra::extract(i, 3) << std::endl;
    std::cout << num_iters << std::endl;
}
