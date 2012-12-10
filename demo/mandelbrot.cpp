#include <limits>
#include <cstdlib>
#include <iostream>
#include "../sierra.h"
#include "../timing.h"

using namespace sierra;

const char* title[9] = { 0, "scalar", 0, 0, "SSE", 0, 0, 0, "AVX" };
const int     row[9] = { 0, 0,        0, 0, 1,     0, 0, 0, 2 };
static unsigned int width = 1024; 
static unsigned int height = 768;
static float x0 = -2; static float x1 = 1;
static float y0 = -1; static float y1 = 1;
static int max_iter = 256;

template<int L>
int varying(L) mandel(float varying(L) c_re, float varying(L) c_im, int count) {
    float varying(L) z_re = c_re;
    float varying(L) z_im = c_im;

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
                int width, int height, int max_iter, int varying(L)* output) 
{
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; i += L) {
            float varying(L) x = x0 + (i + program_index(L)) * dx;
            float varying(L) y = y0 + j * dy;

            *output++ = mandel<L>(x, y, max_iter);
        }
    }
}

template<int L>
void benchmark(int* buf) {
    double min_l = std::numeric_limits<double>::infinity();
    for (int i = 0; i < 3; ++i) {
        reset_and_start_timer();
        mandelbrot<L>(x0, y0, x1, y1, width, height, max_iter, (int varying(L)*) buf);
        double dt = get_elapsed_mcycles();
        min_l = std::min(min_l, dt);
    }
    std::cout << row[LENGTH] << " " << min_l << " " << title[LENGTH] << std::endl;
}

int main() {
    int *buf;
    posix_memalign((void**)&buf, 32, sizeof(int)*width*height);
    benchmark<LENGTH>(buf);
    return 0;
}
