/*
 * Copyright (c) 2010-2012, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 */

#include <algorithm>
#include <iostream>
#include <cstdio>

#include "sierra/sierra.h"
#include "sierra/benchmark.h"

using namespace sierra;

#define L LENGTH
#define MAX_ITER 256

static inline int varying(L) mandel(float varying(L) c_re, float varying(L) c_im) {
    auto z_re = c_re;
    auto z_im = c_im;
    int varying(L) i = 0;
    auto b = z_re * z_re + z_im * z_im;
    for (; (i < MAX_ITER && b < 4.f); ++i) {
        auto new_re = z_re*z_re - z_im*z_im;
        auto new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;
   	b = z_re * z_re + z_im * z_im;
    }

    return i;
}

static void mandelbrot(float x0, float y0, float x1, float y1, int width, int height, int* output) {
    auto dx = (x1 - x0) / width;
    auto dy = (y1 - y0) / height;

    auto p = (int varying(L)*) output;
    for (int j = 0; j < height; ++j) {
        for (int ii = 0; ii < width; ii += L) {
            auto i = ii + program_index(L);
            auto x = x0 + i * dx;
            auto y = y0 + j * dy;
            *p++ = mandel(x, y);
        }
    }
}

static void writePPM(int *buf, int width, int height, const char *fn) {
    FILE* fp = fopen(fn, "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "255\n");
    for (int i = 0; i < width*height; ++i) {
        // map the iteration count to colors by just alternating between two greys
        char c = (buf[i] & 0x1) ? 240 : 20;
        for (int j = 0; j < 3; ++j)
            fputc(c, fp);
    }
    fclose(fp);
    printf("wrote image file %s\n", fn);
}

int main(int argc, char** argv) {
    int num_iters = 1, width = 1920, height = 1200;

    if (argc == 2) {
        num_iters = atoi(argv[1]);
    } else if (argc != 1) {
        const char* exe = argc > 0 ? argv[0] : "mandelbrot";
        std::cout << "usage: " << exe << " [number of iterations]" << std::endl;
        return EXIT_FAILURE;
    }

    float x0 = -2.f, x1 = 1.f;
    float y0 = -1.f, y1 = 1.f;
    auto buf = new int[width*height];

    benchmark([&] { mandelbrot(x0, y0, x1, y1, width, height, buf); }, num_iters);
    writePPM(buf, width, height, "out.ppm");

    delete[] buf;
}
