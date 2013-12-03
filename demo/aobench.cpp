#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <iostream>

#include <SDL2/SDL.h>

#include "sierra/sierra.h"
#include "sierra/timing.h"

#define L LENGTH
#include "sierra/vec3.h"
#include "sierra/random.h"

#define NAO_SAMPLES	2
#define NSUBSAMPLES 8
#define NSUBSAMPLES 8

using namespace sierra;

struct Isect {
    float t;
    vec3  p;
    vec3  n;
    int   hit; 
};

struct Sphere {
    vec3  center;
    float radius;
};

struct Plane {
    vec3 p;
    vec3 n;
};

struct Ray {
    vec3 org;
    vec3 dir;
};

SDL_Surface* surface;
SDL_Window* window;

static spmd(L)
void ray_plane_intersect(Isect varying(L)& isect, Ray varying(L)& ray, Plane& plane) {
    float varying(L) d = -uniform_dot(plane.p, plane.n);
    vec3 varying(L) plane_n;
    splat(plane_n, plane.n);
    float varying(L) v = dot(ray.dir, plane_n);

    if (fabs(v) >= 1.0e-17f) {
        float varying(L) t = -(dot(ray.org, plane_n) + d) / v;

        if ((t > 0.0f) && (t < isect.t)) {
            isect.t = t;
            isect.hit = 1;
            //isect.p = ray.org + ray.dir * t;
            mul(isect.p, ray.dir, t);
            add_assign(isect.p, ray.org);
            copy(isect.n, plane_n);
        }
    }
}

static spmd(L)
void ray_sphere_intersect(Isect varying(L)& isect, Ray varying(L)& ray, Sphere& sphere) {
    vec3 varying(L) sphere_center;
    splat(sphere_center, sphere.center);

    //vec3 rs = ray.org - sphere.center;
    vec3 varying(L) rs;
    sub(rs, ray.org, sphere_center);

    float varying(L) B = dot(rs, ray.dir);
    float varying(L) C = dot(rs, rs) - sphere.radius * sphere.radius;
    float varying(L) D = B * B - C;

    if (D > 0.f) {
        float varying(L) t = -B - sqrt(D);

        if ((t > 0.0f) && (t < isect.t)) {
            isect.t = t;
            isect.hit = 1;
            //isect.p = ray.org + t * ray.dir;
            mul(isect.p, ray.dir, t);
            add_assign(isect.p, ray.org);
            //isect.n = isect.p - sphere.center;
            sub(isect.n, isect.p, sphere_center);
            normalize(isect.n);
        }
    }
}

static spmd(L)
void orthoBasis(vec3 varying(L) basis[3], vec3 varying(L) n) {
    copy(basis[2], n);
    basis[1].x = 0.0f; 
    basis[1].y = 0.0f; 
    basis[1].z = 0.0f;

    if ((n.x < 0.6f) && (n.x > -0.6f)) {
        basis[1].x = 1.0f;
    } else if ((n.y < 0.6f) && (n.y > -0.6f)) {
        basis[1].y = 1.0f;
    } else if ((n.z < 0.6f) && (n.z > -0.6f)) {
        basis[1].z = 1.0f;
    } else {
        basis[1].x = 1.0f;
    }

    //basis[0] = vcross(basis[1], basis[2]);
    cross(basis[0], basis[1], basis[2]);
    normalize(basis[0]);

    //basis[1] = vcross(basis[2], basis[0]);
    cross(basis[1], basis[2], basis[0]);
    normalize(basis[1]);
}


static spmd(L)
float varying(L) ambient_occlusion(Isect varying(L)& isect, Plane& plane, Sphere spheres[3], RNGState varying(L)& rngstate) {
    static float const eps = 0.0001f;
    vec3 varying(L) p;
    vec3 varying(L) n;
    vec3 varying(L) basis[3];
    float varying(L) occlusion = 0.0f;

    //p = isect.p + eps * isect.n;
    mul(p, isect.n, eps);
    add_assign(p, isect.p);

    orthoBasis(basis, isect.n);

    static const int ntheta = NAO_SAMPLES;
    static const int nphi   = NAO_SAMPLES;
    for (int j = 0; j < ntheta; j++) {
        for (int i = 0; i < nphi; i++) {
            Ray varying(L) ray;
            Isect varying(L) occIsect;

            float varying(L) theta = sqrt(frandom(rngstate));
            float varying(L) phi   = 2.0f * M_PI * frandom(rngstate);
            //float varying(L) x = fast_cos(phi) * theta;
            //float varying(L) y = fast_sin(phi) * theta;
            float varying(L) sin_phi;
            float varying(L) cos_phi;
            sincos(phi, sin_phi, cos_phi);
            float varying(L) x = cos_phi * theta;
            float varying(L) y = sin_phi * theta;

            float varying(L) z = sqrt(1.0f - theta * theta);

            // local . global
            float varying(L) rx = x * basis[0].x + y * basis[1].x + z * basis[2].x;
            float varying(L) ry = x * basis[0].y + y * basis[1].y + z * basis[2].y;
            float varying(L) rz = x * basis[0].z + y * basis[1].z + z * basis[2].z;

            copy(ray.org, p);
            ray.dir.x = rx;
            ray.dir.y = ry;
            ray.dir.z = rz;

            occIsect.t   = 1.0e+17f;
            occIsect.hit = 0;

            for (uniform int snum = 0; snum < 3; ++snum)
                ray_sphere_intersect(occIsect, ray, spheres[snum]); 

            ray_plane_intersect(occIsect, ray, plane); 

            if (occIsect.hit) 
                occlusion += 1.0f;
        }
    }

    occlusion = (ntheta * nphi - occlusion) / (float)(ntheta * nphi);
    return occlusion;
}

static void ao(int w, int h, float image[]) {
    static Plane plane = {{ 0.0f, -0.5f, 0.0f }, { 0.f, 1.f, 0.f }};
    static Sphere spheres[3] = {{{ -2.0f, 0.0f, -3.5f }, 0.5f },
                                {{ -0.5f, 0.0f, -3.0f }, 0.5f },
                                {{  1.0f, 0.0f, -2.2f }, 0.5f }};

    RNGState varying(L) rngstate;
    seed_rng(rngstate, seq<L>());
    float invSamples = 1.f / NSUBSAMPLES;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int u = 0; u < NSUBSAMPLES; ++u) {
                for (int vv = 0; vv < NSUBSAMPLES; vv += L) {
                    int varying(L) v = vv + seq<L>();
                    float du = (float)u * invSamples;
                    float varying(L) dv = (float varying(L))v * invSamples;

                    // Figure out x,y pixel in NDC
                    float            px =  (x + du - (w / 2.0f)) / (w / 2.0f);
                    float varying(L) py = -(y + dv - (h / 2.0f)) / (h / 2.0f);
                    //float varying(L) ret = 0.f;
                    Ray varying(L) ray;
                    Isect varying(L) isect;
                    create(ray.org, 0.f, 0.f, 0.f);

                    // Poor man's perspective projection
                    ray.dir.x = px;
                    ray.dir.y = py;
                    ray.dir.z = -1.0f;
                    normalize(ray.dir);

                    isect.t   = 1.0e+17f;
                    isect.hit = 0;

                    for (int snum = 0; snum < 3; ++snum)
                        ray_sphere_intersect(isect, ray, spheres[snum]);

                    ray_plane_intersect(isect, ray, plane);

                    if (isect.hit) {
                        float varying(L) ret = ambient_occlusion(isect, plane, spheres, rngstate);
                        ret *= invSamples * invSamples;

                        float result = 0.f;
                        for (int i = 0; i < L; ++i)
                            result += extract(ret, i);


                        image[3 * (y * w + x) + 0] += result;
                        image[3 * (y * w + x) + 1] += result;
                        image[3 * (y * w + x) + 2] += result;
                    }
                }
            }
            uint8_t val = image[3 * (y * w + x) + 0] * 255.f;
            ((uint8_t*) surface->pixels)[4 * (y * w + x) + 0] = val;
            ((uint8_t*) surface->pixels)[4 * (y * w + x) + 1] = val;
            ((uint8_t*) surface->pixels)[4 * (y * w + x) + 2] = val;
            ((uint8_t*) surface->pixels)[4 * (y * w + x) + 3] = val;
        }
        SDL_UpdateWindowSurface(window);
    }
}

static unsigned char *img;
static float *fimg;

static unsigned char clamp(float f) {
    int i = (int)(f * 255.5);

    if (i < 0) i = 0;
    if (i > 255) i = 255;

    return (unsigned char)i;
}

static void savePPM(const char *fname, int w, int h) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++)  {
            img[3 * (y * w + x) + 0] = clamp(fimg[3 *(y * w + x) + 0]);
            img[3 * (y * w + x) + 1] = clamp(fimg[3 *(y * w + x) + 1]);
            img[3 * (y * w + x) + 2] = clamp(fimg[3 *(y * w + x) + 2]);
        }
    }

    FILE *fp = fopen(fname, "wb");
    if (!fp) {
        perror(fname);
        exit(1);
    }

    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");
    fwrite(img, w * h * 3, 1, fp);
    fclose(fp);
    printf("Wrote image file %s\n", fname);
}

int main(int argc, char **argv) {
    int num_iters = 1;
    int width = 1024;
    int height = 768;

    if (argc == 4) {
        num_iters = atoi(argv[1]);
        width     = atoi(argv[2]);
        height    = atoi(argv[3]);
    } else if (argc != 1) {
        const char* exe = argc > 0 ? argv[0] : "aobench";
        std::cout << "Usage: " << exe << " [number of test iterations] [width] [height] " << std::endl;
        return -1;
    }

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Ambient Occlusion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    SDL_DisplayMode mode;
    mode.w = width;
    mode.h = height;
    mode.refresh_rate = 0;
    mode.format = SDL_PIXELFORMAT_RGB24;
    mode.driverdata = 0;
    SDL_SetWindowDisplayMode(window, &mode);
    surface = SDL_GetWindowSurface(window);

    // Allocate space for output images
    img = new unsigned char[width * height * 3];
    fimg = new float[width * height * 3];
    memset((void *)fimg, 0, sizeof(float) * width * height * 3);

    reset_and_start_timer();
    ao(width, height, fimg);
    std::cout << get_elapsed_mcycles() << std::endl;

    savePPM("out.ppm", width, height); 

    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
