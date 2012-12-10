int mandel(float c_re, float c_im, int count) {
    float z_re = c_re;
    float z_im = c_im;

    int i = 0;
    while ((i < count) & (z_re * z_re + z_im * z_im < 4.f)) {
        float new_re = z_re*z_re - z_im*z_im;
        float new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;

        i = i + 1;
    }

    return i;
}

__kernel
void mandelbrot(float x0, float y0, float x1, float y1, 
                int width, int height, int max_iter, __global int* output) 
{
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = x0 + (i + get_global_id(0)) * dx;
            float y = y0 + j * dy;

            *output++ = mandel(x, y, max_iter);
        }
    }
}
