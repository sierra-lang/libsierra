/*
 * Copyright (c) 2010-2012, Intel Corporation
 * Copyright (c) 2013-2014, Saarland University
 *
 * compile with:
 *  clang++ -std=c++11 -fsierra -O2 -ffast-math -mavx volume.cpp -I../.. -DLENGTH=1
 *  clang++ -std=c++11 -fsierra -O2 -ffast-math -mavx volume.cpp -I../.. -DLENGTH=8
 */

#include <cassert>
#include <cmath>
#include <cstdio>

#include <algorithm>
#include <iostream>

#include "sierra/sierra.h"
#include "sierra/ostream.h"
#include "sierra/benchmark.h"

#define L LENGTH
#include "sierra/math.h"
#include "sierra/vec3.h"

using namespace sierra;

struct Ray {
    vec3 origin;
    vec3 dir;
};

static void generateRay(const float raster2camera[4][4], const float camera2world[4][4], int const varying(L) x, int const varying(L) y, Ray varying(L)& ray) {
  // transform raster coordinate (x, y, 0) to camera space
  auto camx = raster2camera[0][0] * x + raster2camera[0][1] * y + raster2camera[0][3];
  auto camy = raster2camera[1][0] * x + raster2camera[1][1] * y + raster2camera[1][3];
  auto camz = raster2camera[2][3];
  auto camw = raster2camera[3][3];
  camx /= camw;
  camy /= camw;
  camz /= camw;

  ray.dir.x = camera2world[0][0] * camx + camera2world[0][1] * camy + camera2world[0][2] * camz;
  ray.dir.y = camera2world[1][0] * camx + camera2world[1][1] * camy + camera2world[1][2] * camz;
  ray.dir.z = camera2world[2][0] * camx + camera2world[2][1] * camy + camera2world[2][2] * camz;

  ray.origin.x = camera2world[0][3] / camera2world[3][3];
  ray.origin.y = camera2world[1][3] / camera2world[3][3];
  ray.origin.z = camera2world[2][3] / camera2world[3][3];

}

static spmd(L)
int varying(L) Inside(vec3 const varying(L)& p, vec3 const varying(L)& pMin, vec3 const varying(L)& pMax) {
    int varying(L) res = false;

    if (p.x >= pMin.x && p.x <= pMax.x && p.y >= pMin.y && p.y <= pMax.y && p.z >= pMin.z && p.z <= pMax.z)
        res = true;

    return res;
}

static spmd(L)
int varying(L) intersect(Ray varying(L)& ray, vec3 varying(L)& pMin, vec3 varying(L)& pMax, float varying(L)& hit0, float varying(L)& hit1) {
    int varying(L) res = false;
    float varying(L) t0 = -1e30f;
    float varying(L) t1 = 1e30f;

    //float3 tNear = (pMin - ray.origin) / ray.dir;
    vec3 varying(L) tNear;
    copy( tNear, pMin );

    sub_assign( tNear, ray.origin );
    div_assign( tNear, ray.dir );
    //float3 tFar  = (pMax - ray.origin) / ray.dir;
    vec3 varying(L) tFar;
    copy( tFar, pMax );
    sub_assign( tFar, ray.origin );
    div_assign( tFar, ray.dir );

    if (tNear.x > tFar.x) {
        auto tmp = tNear.x;
        tNear.x = tFar.x;
        tFar.x = tmp;
    }
    //t0 = max(tNear.x, t0);
    t0 = fmax( tNear.x, t0 );
    //t1 = min(tFar.x, t1);
    t1 = fmin( tFar.x, t1 );

    if (tNear.y > tFar.y) {
        auto tmp = tNear.y;
        tNear.y = tFar.y;
        tFar.y = tmp;
    }
    //t0 = max(tNear.y, t0);
    t0 = fmax( tNear.y, t0 );
    //t1 = min(tFar.y, t1);
    t1 = fmin( tFar.y, t1 );

    if (tNear.z > tFar.z) {
        auto tmp = tNear.z;
        tNear.z = tFar.z;
        tFar.z = tmp;
    }

    //t0 = max(tNear.z, t0);
    t0 = fmax( tNear.z, t0 );
    //t1 = min(tFar.z, t1);
    t1 = fmin( tFar.z, t1 );

    if (t0 <= t1) {
        hit0 = t0;
        hit1 = t1;
        res = true;
    }

    return res;
}

static spmd(L)
float varying(L) lerp(float varying(L) t, float varying(L) a, float varying(L) b) {
    return (1.f - t) * a + t * b;
}


static spmd(L)
int varying(L) clamp(int varying(L) v, int varying(L) low, int varying(L) high) {
    return imin(imax(v, low), high);
}

static spmd(L)
float varying(L) lookup(int varying(L) x, int varying(L) y, int varying(L) z, int nVoxels[3], float volume[]) {
    x = clamp(x, 0, nVoxels[0]-1);
    y = clamp(y, 0, nVoxels[1]-1);
    z = clamp(z, 0, nVoxels[2]-1);
    auto pos = z*nVoxels[0]*nVoxels[1] + y*nVoxels[0] + x;

    return fgather(volume, pos);
}

static spmd(L)
void offset(vec3 varying(L)& res, vec3 const varying(L)& p, vec3 const varying(L)& pMin, vec3 const varying(L)& pMax) {
  vec3 varying(L) tmp;
  copy( tmp, pMax );
  sub_assign( tmp, pMin ); // pMax - pMin
  copy( res, p );
  sub_assign( res, pMin ); // p - pMin
  div_assign( res, tmp );  //(p - pMin) / (pMax - pMin)
}

static spmd(L)
float varying(L) density(vec3 varying(L)& Pobj, vec3 varying(L)& pMin, vec3 varying(L)& pMax, float volume[], int nVoxels[3]) {
    float varying(L) res = 0;

    if (Inside(Pobj, pMin, pMax)) {
        // Compute voxel coordinates and offsets for _Pobj_
        //float3 vox = Offset(Pobj, pMin, pMax);
        vec3 varying(L) vox;
        offset( vox, Pobj, pMin, pMax ); // init vox
        vox.x = vox.x * nVoxels[0] - .5f;
        vox.y = vox.y * nVoxels[1] - .5f;
        vox.z = vox.z * nVoxels[2] - .5f;
        auto vx = (int varying(L))(vox.x);
        auto vy = (int varying(L))(vox.y);
        auto vz = (int varying(L))(vox.z);
        auto dx = vox.x - vx, dy = vox.y - vy, dz = vox.z - vz;

        // Trilinearly interpolate volume values to compute local density
        auto d00 = lerp(dx, lookup(vx, vy+0, vz+0, nVoxels, volume), lookup(vx+1, vy+0, vz+0, nVoxels, volume));
        auto d10 = lerp(dx, lookup(vx, vy+1, vz+0, nVoxels, volume), lookup(vx+1, vy+1, vz+0, nVoxels, volume));
        auto d01 = lerp(dx, lookup(vx, vy+0, vz+1, nVoxels, volume), lookup(vx+1, vy+0, vz+1, nVoxels, volume));
        auto d11 = lerp(dx, lookup(vx, vy+1, vz+1, nVoxels, volume), lookup(vx+1, vy+1, vz+1, nVoxels, volume));
        auto d0 = lerp(dy, d00, d10);
        auto d1 = lerp(dy, d01, d11);
        res = lerp(dz, d0, d1);
    }

    return res;
}

static spmd(L)
float varying(L) transmittance(vec3 varying(L)& p0, vec3 varying(L)& p1, vec3 varying(L)& pMin, vec3 varying(L)& pMax, float sigma_t, float volume[], int nVoxels[3]) {
    float varying(L) rayT0;
    float varying(L) rayT1;

    Ray varying(L) ray;
    //ray.origin = p1;
    copy( ray.origin, p1 );
    //ray.dir = p0 - p1;
    copy( ray.dir, p0 );
    sub_assign( ray.dir, p1 ); // p0 - p1

    float varying(L) res = 1.f;

    // Find the parametric t range along the ray that is inside the volume.
    if (intersect(ray, pMin, pMax, rayT0, rayT1)) {
        rayT0 = fmax(rayT0, 0.f);

        // Accumulate beam transmittance in tau
        float varying(L) tau = 0;
        auto rayLength = sqrt(ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z);
        static float const stepDist = 0.2f;
        auto stepT = stepDist / rayLength;

        auto t = rayT0;
        //float3 pos = ray.origin + ray.dir * rayT0;
        vec3 varying(L) pos;
        copy( pos, ray.dir );
        mul_assign( pos, rayT0 );
        add_assign( pos, ray.origin );
        //float3 dirStep = ray.dir * stepT;
        vec3 varying(L) dirStep;
        copy( dirStep, ray.dir );
        mul_assign( dirStep, stepT );
        while (t < rayT1) {
            tau += stepDist * sigma_t * density(pos, pMin, pMax, volume, nVoxels);
            //pos = pos + dirStep;
            add_assign( pos, dirStep );
            t += stepT;
        }
        res = exp(-tau);
    }

    return res;
}

static spmd(L)
float varying(L) distanceSquared(vec3 varying(L)& a, vec3 varying(L)& b) {
    //float3 d = a-b;
    //return d.x*d.x + d.y*d.y + d.z*d.z;
    vec3 varying(L) d;
    copy( d, a );
    sub_assign( d, b );
    return d.x*d.x + d.y*d.y + d.z*d.z;
}

static float varying(L) raymarch(float volume[], int nVoxels[3], Ray varying(L)& ray) {
    float varying(L) result = 0.f; // radiance along the ray
    float varying(L) rayT0;
    float varying(L) rayT1;

    //float3 pMin(.3f, -.2f, .3f), pMax(1.8f, 2.3f, 1.8f);
    vec3 varying(L) pMin;
    create(pMin, .3f, -.2f, .3f);

    vec3 varying(L) pMax;
    create(pMax, 1.8f, 2.3f, 1.8f);

    //float3 lightPos(-1.f, 4.f, 1.5f);
    vec3 varying(L) lightPos;
    create(lightPos, -1.f, 4.f, 1.5f);

    if (intersect(ray, pMin, pMax, rayT0, rayT1)) {
        rayT0 = fmax(rayT0, 0.f);

        // Parameters that define the volume scattering characteristics and
        // sampling rate for raymarching
        static float const Le = .25f;           // Emission coefficient
        static float const sigma_a = 10;        // Absorption coefficient
        static float const sigma_s = 10;        // Scattering coefficient
        static float const stepDist = 0.025f;   // Ray step amount
        static float const lightIntensity = 40; // Light source intensity

        float varying(L) tau = 0.f;  // accumulated beam transmittance
        auto rayLength = sqrt(dot(ray.dir, ray.dir));
        auto stepT = stepDist / rayLength;
        auto t = rayT0;

        //float3 pos = ray.dir * rayT0 + ray.origin;
        vec3 varying(L) pos;
        copy( pos, ray.dir );
        mul_assign( pos, rayT0 );
        add_assign( pos, ray.origin );
        //float3 dirStep = ray.dir * stepT;
        vec3 varying(L) dirStep;
        copy( dirStep, ray.dir );
        mul_assign( dirStep, stepT );

        int varying(L) attenMask = true;
        while (attenMask && t < rayT1) {
            auto d = density(pos, pMin, pMax, volume, nVoxels);

            // terminate once attenuation is high
            auto atten = exp(-tau);
            if (atten < .005f)
                attenMask = false;
            else {
                // direct lighting
                auto Li = lightIntensity / distanceSquared(lightPos, pos)
                    * transmittance(lightPos, pos, pMin, pMax, sigma_a + sigma_s, volume, nVoxels);
                result += stepDist * atten * d * sigma_s * (Li + Le);

                // update beam transmittance
                tau += stepDist * (sigma_a + sigma_s) * d;

                //pos = pos + dirStep;
                add_assign( pos, dirStep );
                t += stepT;
            }
        }
        // Gamma correction
        result = pow(result, 1.f / 2.2f);
    }

    return result;
}

static void render(float volume[], int nVoxels[3], const float raster2camera[4][4], const float camera2world[4][4], int width, int height, float image[]) {
    static const int xoffsets[16] = { 0, 1, 0, 1, 2, 3, 2, 3,
                                      0, 1, 0, 1, 2, 3, 2, 3 };
    static const int yoffsets[16] = { 0, 0, 1, 1, 0, 0, 1, 1,
                                      2, 2, 3, 3, 2, 2, 3, 3 };

    auto xOffsetPtr = (int varying(L)*) xoffsets;
    auto yOffsetPtr = (int varying(L)*) yoffsets;

    for (int y = 0; y < height; y += Tile<L>::y) {
        for (int x = 0; x < width; x += Tile<L>::x) {
            Ray varying(L) ray;

            auto xo = (float varying(L)) (x + *xOffsetPtr);
            auto yo = (float varying(L)) (y + *yOffsetPtr);

            generateRay(raster2camera, camera2world, xo, yo, ray);
            auto res = raymarch(volume, nVoxels, ray);

            for (int off = 0; off < L; ++off)
                image[(y + yoffsets[off]) * width + x + xoffsets[off]] = extract( res, off );
        }
    }
}

static void writePPM(float *buf, int width, int height, const char *fn) {
    FILE *fp = fopen(fn, "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "255\n");
    for (int i = 0; i < width*height; ++i) {
        float v = buf[i] * 255.f;
        if (v < 0.f) v = 0.f;
        else if (v > 255.f) v = 255.f;
        auto c = uint8_t(v);
        for (int j = 0; j < 3; ++j)
            fputc(c, fp);
    }
    fclose(fp);
    printf("Wrote image file %s\n", fn);
}

static void loadCamera(const char *fn, int& width, int& height, float raster2camera[4][4], float camera2world[4][4]) {
    FILE *f = fopen(fn, "r");
    if (!f) {
        perror(fn);
        exit(1);
    }
    if (fscanf(f, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "Unexpected end of file in camera file\n");
        exit(1);
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (fscanf(f, "%f", &raster2camera[i][j]) != 1) {
                fprintf(stderr, "Unexpected end of file in camera file\n");
                exit(1);
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (fscanf(f, "%f", &camera2world[i][j]) != 1) {
                fprintf(stderr, "Unexpected end of file in camera file\n");
                exit(1);
            }
        }
    }
    fclose(f);
}

static float* loadVolume(const char *fn, int n[3]) {
    FILE *f = fopen(fn, "r");
    if (!f) {
        perror(fn);
        exit(1);
    }

    if (fscanf(f, "%d %d %d", &n[0], &n[1], &n[2]) != 3) {
        fprintf(stderr, "Couldn't find resolution at start of density file\n");
        exit(1);
    }

    int count = n[0] * n[1] * n[2];
    float *v = new float[count];
    for (int i = 0; i < count; ++i) {
        if (fscanf(f, "%f", &v[i]) != 1) {
            fprintf(stderr, "Unexpected end of file at %d'th density value\n", i);
            exit(1);
        }
    }

    return v;
}

int main(int argc, char** argv) {
    int width, height, num_iters = 1;
    float raster2camera[4][4], camera2world[4][4];
    float* volume;
    int n[3];
    const char* exe = argc > 0 ? argv[0] : "volume";

    if (argc != 3) {
        std::cout << "usage: " << exe << " <camara.dat> <volume.vol>" << std::endl;
        return EXIT_FAILURE;
    }

    loadCamera(argv[1], width, height, raster2camera, camera2world);
    volume = loadVolume(argv[2], n);
    auto image = new float[width*height];

    std::cout << "volume renderer: " << benchmark([&] { render(volume, n, raster2camera, camera2world, width, height, image); }) << std::endl;
    writePPM(image, width, height, "out.ppm");

    delete[] image;
}
