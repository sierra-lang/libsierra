#include <cstdlib>
#include <iostream>

#include "sierra/sierra.h"
#include "sierra/timing.h"

#define N 1048576

alignas(16) float r[N+10000];
alignas(16) float g[N+20000];
alignas(16) float b[N+30000];
alignas(16) float gray[N+40000];

void serial_rgb2gray(float* ra, float* ga, float* ba, float* gray) {
    for (int i = 0; i < N; i++)
            gray[i] = 0.3f * ra[i] + 0.59f * ga[i] + 0.11f * ba[i];
}

int main (int argc, char* argv[]) {
    for(int i = 0; i < N; i++) {
        r[N] = random() % 256;
        g[N] = random() % 256;
        b[N] = random() % 256;
    }
    std::cout<< "Convert " << N << " pixels RGB to gray." << std::endl;
}
