#include <cassert>
#include <cmath>
#include <cstdio>

#include <algorithm>
#include <iostream>

#include "sierra/sierra.h"
#include "sierra/ostream.h"
#include "sierra/timing.h"

#define L LENGTH
#include "sierra/math.h"
#include "sierra/vec3.h"

using namespace sierra;

template<int>
struct LSQRT {};

template<>
struct LSQRT<1> {
    static int const x = 1;
    static int const y = 1;
};

template<>
struct LSQRT<2> {
    static int const x = 2;
    static int const y = 1;
};

template<>
struct LSQRT<4> {
    static int const x = 2;
    static int const y = 2;
};

template<>
struct LSQRT<8> {
    static int const x = 4;
    static int const y = 2;
};

template<>
struct LSQRT<16> {
    static int const x = 4;
    static int const y = 4;
};

struct Ray {
    vec3 origin;
    vec3 dir;
};

static void generateRay(const float raster2camera[4][4], const float camera2world[4][4], int const varying(L) x, int const varying(L) y, Ray varying(L)& ray) {
  // transform raster coordinate (x, y, 0) to camera space
  float varying(L) camx = raster2camera[0][0] * x + raster2camera[0][1] * y + raster2camera[0][3];
  float varying(L) camy = raster2camera[1][0] * x + raster2camera[1][1] * y + raster2camera[1][3];
  float varying(L) camz = raster2camera[2][3];
  float varying(L) camw = raster2camera[3][3];
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

    if (p.x >= pMin.x && p.x <= pMax.x &&
            p.y >= pMin.y && p.y <= pMax.y &&
            p.z >= pMin.z && p.z <= pMax.z)
        res = true;

    return res;
}

static spmd(L) int varying(L) intersect(Ray varying(L)& ray, vec3 varying(L)& pMin, vec3 varying(L)& pMax, float varying(L)& hit0, float varying(L)& hit1) {
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
        float const varying(L) tmp = tNear.x;
        tNear.x = tFar.x;
        tFar.x = tmp;
    }
    //t0 = max(tNear.x, t0);
    t0 = fmax( tNear.x, t0 );
    //t1 = min(tFar.x, t1);
    t1 = fmin( tFar.x, t1 );

    if (tNear.y > tFar.y) {
        float const varying(L) tmp = tNear.y;
        tNear.y = tFar.y;
        tFar.y = tmp;
    }
    //t0 = max(tNear.y, t0);
    t0 = fmax( tNear.y, t0 );
    //t1 = min(tFar.y, t1);
    t1 = fmin( tFar.y, t1 );

    if (tNear.z > tFar.z) {
        float const varying(L) tmp = tNear.z;
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

  spmd(L)
static float varying(L)
  Lerp(float varying(L) t, float varying(L) a, float varying(L) b) {
    return (1.f - t) * a + t * b;
  }


static spmd(L)
int varying(L) Clamp(int varying(L) v, int varying(L) low, int varying(L) high) {
    return imin(imax(v, low), high);
}

static spmd(L)
float varying(L) D(int varying(L) x, int varying(L) y, int varying(L) z, int nVoxels[3], float density[]) {
    x = Clamp(x, 0, nVoxels[0]-1);
    y = Clamp(y, 0, nVoxels[1]-1);
    z = Clamp(z, 0, nVoxels[2]-1);
    int varying(L) pos = z*nVoxels[0]*nVoxels[1] + y*nVoxels[0] + x;

    return fgather(density, pos);
}


static spmd(L)
void offset(vec3 varying(L)& res, vec3 const varying(L)& p, vec3 const varying(L)& pMin, vec3 const varying(L)& pMax) {
  vec3 varying(L) tmp;
  copy( tmp, pMax );
  sub_assign( tmp, pMin ); // pMax - pMin
  copy( res, p );
  sub_assign( res, pMin ); // p - pMin
  div_assign( res, tmp ); // (p - pMin) / (pMax - pMin)
}

  spmd(L)
static inline float varying(L)
  Density(vec3 varying(L)& Pobj, vec3 varying(L)& pMin,
      vec3 varying(L)& pMax, float density[], int nVoxels[3]) {
    float varying(L) res = 0;

    if (Inside(Pobj, pMin, pMax)) 
    {
      // Compute voxel coordinates and offsets for _Pobj_
      //float3 vox = Offset(Pobj, pMin, pMax);
      vec3 varying(L) vox;
      offset( vox, Pobj, pMin, pMax ); // init vox
      vox.x = vox.x * nVoxels[0] - .5f;
      vox.y = vox.y * nVoxels[1] - .5f;
      vox.z = vox.z * nVoxels[2] - .5f;
      int varying(L) vx = (int varying(L))(vox.x);
      int varying(L) vy = (int varying(L))(vox.y);
      int varying(L) vz = (int varying(L))(vox.z);
      float varying(L) dx = vox.x - vx, dy = vox.y - vy, dz = vox.z - vz;

      // Trilinearly interpolate density values to compute local density
      float varying(L) d00 = Lerp(dx, D(vx, vy, vz, nVoxels, density),     
          D(vx+1, vy, vz, nVoxels, density));
      float varying(L) d10 = Lerp(dx, D(vx, vy+1, vz, nVoxels, density),   
          D(vx+1, vy+1, vz, nVoxels, density));
      float varying(L) d01 = Lerp(dx, D(vx, vy, vz+1, nVoxels, density),   
          D(vx+1, vy, vz+1, nVoxels, density));
      float varying(L) d11 = Lerp(dx, D(vx, vy+1, vz+1, nVoxels, density), 
          D(vx+1, vy+1, vz+1, nVoxels, density));
      float varying(L) d0 = Lerp(dy, d00, d10);
      float varying(L) d1 = Lerp(dy, d01, d11);
      res = Lerp(dz, d0, d1);
    }
    return res;
  }


static spmd(L)
float varying(L) transmittance(vec3 varying(L)& p0, vec3 varying(L)& p1, vec3 varying(L)& pMin, vec3 varying(L)& pMax, float sigma_t, float density[], int nVoxels[3]) {
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
        float varying(L) rayLength = sqrt(ray.dir.x * ray.dir.x
                + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z);
        float const stepDist = 0.2f;
        float varying(L) stepT = stepDist / rayLength;

        float varying(L) t = rayT0;
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
            tau += stepDist * sigma_t * Density(pos, pMin, pMax, density, nVoxels);
            //pos = pos + dirStep;
            add_assign( pos, dirStep );
            t += stepT;
        }
        res = exp(-tau);
    }

    return res;
}


spmd(L)
static float varying(L)
distanceSquared(vec3 varying(L)& a, vec3 varying(L)& b) {
    //float3 d = a-b;
    //return d.x*d.x + d.y*d.y + d.z*d.z;
    vec3 varying(L) d;
    copy( d, a );
    sub_assign( d, b );
    return d.x*d.x + d.y*d.y + d.z*d.z;
}


static float varying(L)
raymarch(float density[], int nVoxels[3], Ray varying(L)& ray) {
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
        float const Le = .25f;           // Emission coefficient
        float const sigma_a = 10;        // Absorption coefficient
        float const sigma_s = 10;        // Scattering coefficient
        float const stepDist = 0.025f;   // Ray step amount
        float const lightIntensity = 40; // Light source intensity

        float varying(L) tau = 0.f;  // accumulated beam transmittance
        float varying(L) rayLength = sqrt(dot(ray.dir, ray.dir));
        float varying(L) stepT = stepDist / rayLength;

        float varying(L) t = rayT0;

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
            float varying(L) d = Density(pos, pMin, pMax, density, nVoxels);

            // terminate once attenuation is high
            float varying(L) atten = exp(-tau);
            if (atten < .005f)
                attenMask = false;
            else {
                // direct lighting
                float varying(L) Li = lightIntensity / distanceSquared(lightPos, pos) * 
                    transmittance(lightPos, pos, pMin, pMax, sigma_a + sigma_s,
                            density, nVoxels);
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


void volume_sierra(float density[], int nVoxels[3], const float raster2camera[4][4], const float camera2world[4][4], int width, int height, float image[]) {
    const int xoffsets[16] = { 0, 1, 0, 1, 2, 3, 2, 3,
                                0, 1, 0, 1, 2, 3, 2, 3 };
    const int yoffsets[16] = { 0, 0, 1, 1, 0, 0, 1, 1, 
                                2, 2, 3, 3, 2, 2, 3, 3 };

    int const varying(L) *xOffsetPtr = (int varying(L)*) xoffsets;
    int const varying(L) *yOffsetPtr = (int varying(L)*) yoffsets;

    for (int y = 0; y < height; y += LSQRT<L>::y) {
        for (int x = 0; x < width; x += LSQRT<L>::x) {
            Ray varying(L) ray;

            float const varying(L) xo = (float varying(L)) (x + *xOffsetPtr);
            float const varying(L) yo = (float varying(L)) (y + *yOffsetPtr);

            generateRay(raster2camera, camera2world, xo, yo, ray);
            float varying(L) res = raymarch(density, nVoxels, ray);

            for ( int off = 0; off < L; ++off )
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
        unsigned char c = (unsigned char)v;
        for (int j = 0; j < 3; ++j)
            fputc(c, fp);
    }
    fclose(fp);
    printf("Wrote image file %s\n", fn);
}


static void loadCamera(const char *fn, int *width, int *height, float raster2camera[4][4], float camera2world[4][4]) {
    FILE *f = fopen(fn, "r");
    if (!f) {
        perror(fn);
        exit(1);
    }
    if (fscanf(f, "%d %d", width, height) != 2) {
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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: volume <camera.dat> <volume_density.vol>\n");
        return 1;
    }

    //
    // Load viewing data and the volume density data
    //
    int width, height;
    float raster2camera[4][4], camera2world[4][4];
    loadCamera(argv[1], &width, &height, raster2camera, camera2world);
    float *image = new float[width*height];

    int n[3];
    float *density = loadVolume(argv[2], n);

#define NUM 1

    // Compute the image using the sierra implementation.
    double times[NUM];
    for (int i = 0; i < NUM; ++i) {
      reset_and_start_timer();
      volume_sierra(density, n, raster2camera, camera2world, width, height, image);
      times[i] = get_elapsed_mcycles();
      std::cout << times[i] << std::endl;
    }

    std::sort(times, times+NUM);
    std::cout << "median: " << times[NUM/2] << std::endl;

    writePPM(image, width, height, "out.ppm");

    // Clear out the buffer
    for (int i = 0; i < width * height; ++i)
      image[i] = 0.;

    return 0;
}
