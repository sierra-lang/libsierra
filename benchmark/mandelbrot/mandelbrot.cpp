#include <algorithm>
#include <iostream>
#include <cstdio>

#include "sierra/sierra.h"
#include "sierra/timing.h"

using namespace sierra;

#define L LENGTH

static inline int varying(L) mandel(float varying(L) c_re, float uniform c_im, int uniform count) {
    float varying(L) z_re = c_re;
    float varying(L) z_im = c_im;
    int varying(L) i = 0;
    for (; (i < count) & (z_re * z_re + z_im * z_im < 4.f); ++i) {
        float varying(L) new_re = z_re*z_re - z_im*z_im;
        float varying(L) new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;
    }

    return i;
}

static void mandelbrot(float x0, float y0, 
                       float x1, float y1,
                       int width, int height, 
                       int max_iter, int output[])
{
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;

    int varying(L)* p = (int varying(L)*) output;
    for (int j = 0; j < height; ++j) {
        for (int ii = 0; ii < width; ii += L) {
            int varying(L) i = ii + program_index(L);
            float varying(L) x = x0 + i * dx;
            float uniform y = y0 + j * dy;
            *p++ = mandel(x, y, max_iter);
        }
    }
}

/* Write a PPM image file with the image of the Mandelbrot set */
static void
writePPM(int *buf, int width, int height, const char *fn) {
    FILE *fp = fopen(fn, "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "255\n");
    for (int i = 0; i < width*height; ++i) {
        // Map the iteration count to colors by just alternating between
        // two greys.
        char c = (buf[i] & 0x1) ? 240 : 20;
        for (int j = 0; j < 3; ++j)
            fputc(c, fp);
    }
    fclose(fp);
    printf("Wrote image file %s\n", fn);
}

int main() {
    unsigned int width = 1920;
    unsigned int height = 1200;
    float x0 = -2;
    float x1 = 1;
    float y0 = -1;
    float y1 = 1;

    int max_iter = 256;
    //int *buf = new int[width*height];
    int* buf;
    posix_memalign((void**)&buf, 32, sizeof(int)*width*height);


#define NUM_ITER 7
    double times[NUM_ITER];
    for (int i = 0; i < NUM_ITER; ++i) {
        reset_and_start_timer();
        mandelbrot(x0, y0, x1, y1, width, height, max_iter, buf);
        times[i] = get_elapsed_mcycles();
    }
    std::sort(times, times + NUM_ITER);
    std::cout << times[NUM_ITER/2] << std::endl;
    writePPM(buf, width, height, "mandelbrot-sierra.ppm");

    return 0;
}
