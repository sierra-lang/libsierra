#include <algorithm>
#include <limits>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../sierra.h"
#include "../timing.h"

using namespace sierra;

static unsigned int width = 1024;
static unsigned int height = 768;
static float x0 = -2;
static float x1 = 1;
static float y0 = -1;
static float y1 = 1;
static int maxIterations = 256;

template<int L>
int varying(L) mandel(float varying(L) c_re, float varying(L) c_im, int uniform count) {
    float varying(L) z_re = c_re, z_im = c_im;
    int varying(L) i = 0;

    while ((i < count) & (z_re * z_re + z_im * z_im < 4.f)) {
        float varying(L) new_re = z_re*z_re - z_im*z_im;
        float varying(L) new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;

        i = i + 1;
    }

    return i;
}

template<int L>
void mandelbrot(float x0, float y0, float x1, float y1, 
                int width, int height, int maxIterations, int output[]) 
{
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;

    int varying(L) test = 42;

    for (int j = 0; j < height; ++j) {
        for (int ii = 0; ii < width; ii += L) {
            int varying(L) i = ii + program_index(L);
            float varying(L) x = x0 + i * dx;
            float varying(L) y = y0 + j * dy;

            //int varying(L) index = j * width + i;
            int varying(L) val = mandel<L>(x, y, maxIterations);

            int index = (j * width + ii)/L;
            *(((int varying(L)*) &output[0]) + index) = val;

            // TODO this is slow
            //for (int x = 0; x < L; ++x)
                //output[extract(index, x)] = extract(val, x);
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

template<int L>
void benchmark(int* buf) {
    double min_l = std::numeric_limits<double>::infinity();
    for (int i = 0; i < 3; ++i) {
        reset_and_start_timer();
        mandelbrot<L>(x0, y0, x1, y1, width, height, maxIterations, buf);
        double dt = get_elapsed_mcycles();
        min_l = std::min(min_l, dt);
    }
    std::cout << "[mandelbrot sierra " << L << "]:\t\t[" << std::setprecision(6) << min_l << "] million cycles" << std::endl;
    std::ostringstream oss;
    oss << "mandelbrot-" << L << ".ppm";
    writePPM(buf, width, height, oss.str().c_str());
}

int main() {
    int *buf = new int[width*height];

    benchmark<1>(buf);
    benchmark<4>(buf);
    benchmark<8>(buf);

    delete[] buf;

    return 0;
}
