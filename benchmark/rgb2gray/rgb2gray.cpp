/*
 * Copyright (c) 2013-2014, Saarland University
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "sierra/sierra.h"
#include "sierra/timing.h"

#define N 1048576

#if 0

alignas(16) float r[N+10000];
alignas(16) float g[N+20000];
alignas(16) float b[N+30000];
alignas(16) float gray[N+40000];

void serial_rgb2gray(float varying(L)* ra, float varying(L)* ga, float varying(L)* ba, float varying(L)* gray) {
    for (int i = 0; i < N; ++i)
        gray[i] = 0.3f * ra[i] + 0.59f * ga[i] + 0.11f * ba[i];
}

#endif

//struct Image {
    //int width;
    //int height;
//};

//Image create(int width, int height) {
    //Image result;
    //result.r = new float[width*height];
    //result.g = new float[width*height];
    //result.b = new float[width*height];
    //return result;
//}


int read_int(FILE* file) {
    int result = 0;
    while (true) {
        int c = fgetc(file);
        int digit = c - '0';
        if (0 <= digit && digit <= 9) {
            result *= 10;
            result += digit;
        } else {
            ungetc(c, file);
            break;
        }
    }

    return result;
}

int main (int argc, char* argv[]) {
    int width;
    int height;
    float* r = 0;
    float* g = 0;
    float* b = 0;

    // read PPM
    FILE* file = fopen("lena.ppm", "r");
    if (!file)
        return EXIT_FAILURE;

    if (fgetc(file) == 'P' && fgetc(file) == '6' && fgetc(file) == '\n') {
        width = read_int(file);
        if (fgetc(file) == ' ') {
            height = read_int(file);
            if (fgetc(file) == '\n' && fgetc(file) == '2' && fgetc(file) == '5' && fgetc(file) == '5' && fgetc(file) == '\n') {
                r = new[width*height];
                g = new[width*height];
                b = new[width*height];

                while (true) {
                    int ri = fgetc(file);
                    if (ri !=
                }
                i = 0;
                int ri = fgetc(file)
            }
        }
    }
    fclose(file);

#if 0
    for(int i = 0; i < N; i++) {
        r[N] = random() % 256;
        g[N] = random() % 256;
        b[N] = random() % 256;
    }
    std::cout<< "Convert " << N << " pixels RGB to gray." << std::endl;

    reset_and_start_stimer();
    for(int i = 0; i < ITERATIONS; i++) { serial_rgb2gray(r, g, b, gray);}
        double dt = get_elapsed_seconds();
    std::cout<< "serial version: " << dt << " seconds" << std::endl;
#endif

    delete[] r;
    delete[] g;
    delete[] b;

    return EXIT_SUCCESS;
}
