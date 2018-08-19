/*
 * Copyright (c) 2010-2012, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

#include "sierra/sierra.h"
#include "sierra/benchmark.h"

#define L LENGTH
#include "sierra/vec3.h"
#include "sierra/random.h"

#define NAO_SAMPLES	8
#define NSUBSAMPLES 16
#define NSUBSAMPLES 16

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

static spmd(L)
void ray_plane_intersect(Isect &isect, Ray &ray, Plane &plane) {
    auto d =
        plane.p.x * plane.n.x + plane.p.y * plane.n.y + plane.p.z * plane.n.z;
    //auto d = -uniform_dot(plane.p, plane.n);

    auto v =
        ray.dir.x * plane.n.x + ray.dir.y * plane.n.y + ray.dir.z * plane.n.z;
    //auto v = dot(ray.dir, plane.n);

    if (fabs(v) <= 1.0e-17f) {
        return;
    }

    auto t = ray.org.x * plane.n.x + ray.org.y * plane.n.y +
             ray.org.z * plane.n.z;
    t = -(t + d) / v;
    //auto t = -(dot(ray.org, plane.n) + d) / v;

    if ((t > 0.0f) && (t < isect.t)) {
        isect.t = t;
        isect.hit = 1;

        isect.p.x = ray.dir.x * t;
        isect.p.y = ray.dir.y * t;
        isect.p.z = ray.dir.z * t;
        //mul(isect.p, ray.dir, t);

        isect.p.x += ray.org.x;
        isect.p.y += ray.org.y;
        isect.p.z += ray.org.z;
        //add_assign(isect.p, ray.org);

        //isect.n.x = plane.n.x;
        //isect.n.y = plane.n.y;
        //isect.n.z = plane.n.z;
        isect.n = plane.n;
        //copy(isect.n, plane.n);
    }
}


static spmd(L)
void ray_sphere_intersect(Isect &isect, Ray &ray, Sphere &sphere) {
    vec3 rs;

    rs.x = ray.org.x - sphere.center.x;
    rs.y = ray.org.y - sphere.center.y;
    rs.z = ray.org.z - sphere.center.z;
    //sub(rs, ray.org, sphere.center);

    double B = rs.x * ray.dir.x + rs.y * ray.dir.y + rs.z * ray.dir.z;
    //auto B = dot(rs, ray.dir);

    double C = rs.x * rs.x + rs.y * rs.y + rs.z * rs.z;
    C -= sphere.radius * sphere.radius;
    //auto C = dot(rs, rs) - sphere.radius * sphere.radius;

    double D = B * B - C;

    if (D > 0.0) {
        auto t = -B - sqrt(D);

        if ((t > 0.0) && (t < isect.t)) {
            isect.t = t;
            isect.hit = 1;

            isect.p.x = ray.org.x + t * ray.dir.x;
            isect.p.y = ray.org.y + t * ray.dir.y;
            isect.p.z = ray.org.z + t * ray.dir.z;
            //mul(isect.p, ray.dir, t);
            //add_assign(isect.p, ray.org);

            isect.n.x = isect.p.x - sphere.center.x;
            isect.n.y = isect.p.y - sphere.center.y;
            isect.n.z = isect.p.z - sphere.center.z;
            //sub(isect.n, isect.p, sphere_center);

            auto tmp = sqrt(isect.n.x * isect.n.x + isect.n.y * isect.n.y +
                            isect.n.z * isect.n.z);
            isect.n.x /= tmp;
            isect.n.y /= tmp;
            isect.n.z /= tmp;
            //normalize(isect.n);
        }
    }
}

static spmd(L)
void orthoBasis(vec3 *basis, vec3 n) {
    basis[2] = n;
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

    basis[0].x = basis[1].y * basis[2].z - basis[1].z * basis[2].y;
    basis[0].y = basis[1].z * basis[2].x - basis[1].x * basis[2].z;
    basis[0].z = basis[1].x * basis[2].y - basis[1].y * basis[2].x;
    //cross(basis[0], basis[1], basis[2]);

    auto tmp0 = sqrt(basis[0].x * basis[0].x + basis[0].y * basis[0].y +
                     basis[0].z * basis[0].z);
    basis[0].x /= tmp0;
    basis[0].y /= tmp0;
    basis[0].z /= tmp0;
    //normalize(basis[0]);

    basis[1].x = basis[2].y * basis[0].z - basis[2].z * basis[0].y;
    basis[1].y = basis[2].z * basis[0].x - basis[2].x * basis[0].z;
    basis[1].z = basis[2].x * basis[0].y - basis[2].y * basis[0].x;
    //cross(basis[1], basis[2], basis[0]);

    auto tmp1 = sqrt(basis[1].x * basis[1].x + basis[1].y * basis[1].y +
                     basis[1].z * basis[1].z);
    basis[1].x /= tmp1;
    basis[1].y /= tmp1;
    basis[1].z /= tmp1;
    //normalize(basis[1]);
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

            auto theta = sqrt(frandom(rngstate));
            auto phi   = 2.0f * M_PI * frandom(rngstate);
            //float varying(L) x = fast_cos(phi) * theta;
            //float varying(L) y = fast_sin(phi) * theta;
            float varying(L) sin_phi;
            float varying(L) cos_phi;
            sincos(phi, sin_phi, cos_phi);
            auto x = cos_phi * theta;
            auto y = sin_phi * theta;
            auto z = sqrt(1.0f - theta * theta);

            // local . global
            auto rx = x * basis[0].x + y * basis[1].x + z * basis[2].x;
            auto ry = x * basis[0].y + y * basis[1].y + z * basis[2].y;
            auto rz = x * basis[0].z + y * basis[1].z + z * basis[2].z;

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
                    auto v = vv + seq<L>();
                    auto du = (float)u * invSamples;
                    auto dv = (float varying(L))v * invSamples;

                    // Figure out x,y pixel in NDC
                    auto px =  (x + du - (w / 2.0f)) / (w / 2.0f);
                    auto py = -(y + dv - (h / 2.0f)) / (h / 2.0f);
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
                        auto ret = ambient_occlusion(isect, plane, spheres, rngstate);
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
        }
    }
}

static uint8_t clamp(float f) {
    int i = (int)(f * 255.5f);

    if (i < 0) i = 0;
    if (i > 255) i = 255;

    return uint8_t(i);
}

static void writePPM(const char *fname, int w, int h, uint8_t* img, float* fimg) {
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
    printf("wrote image file %s\n", fname);
}

int main(int argc, char** argv) {
    int num_iters = 1, width = 256, height = 256;

    if (argc == 4) {
        width     = atoi(argv[1]);
        height    = atoi(argv[2]);
        num_iters = atoi(argv[3]);
    } else if (argc == 2)
    {
      num_iters = atoi(argv[1]);
    } else if (argc != 1) {
        const char* exe = argc > 0 ? argv[0] : "aobench";
        std::cout << "usage: " << exe << " [width] [height] [number of iterations]" << std::endl;
        return EXIT_FAILURE;
    }

    auto  img = new uint8_t[width * height * 3];
    auto fimg = new float[width * height * 3];

    benchmark([&] { ao(width, height, fimg); }, num_iters);
    writePPM("out.ppm", width, height, img, fimg);

    delete[] img;
    delete[] fimg;
}
