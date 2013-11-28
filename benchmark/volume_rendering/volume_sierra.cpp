/*
  Copyright (c) 2011, Intel Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of Intel Corporation nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.


   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
*/

#include <assert.h>
#include <math.h>
#include <cmath>
#include <algorithm>
#include "../../sierra/sierra.h"
#include "../../sierra/ostream.h"

#include <iostream>

#define L LENGTH
#include "../../sierra/vec3.h"
#undef L

using namespace sierra;

template< int L >
struct LSQRT {};

template<>
struct LSQRT<4> {
  static int const x = 2; }

template<>
struct LSQRT<8> { static int const value = 2; }

struct Ray {
    vec3 origin, dir;
};


static void
generateRay(const uniform float raster2camera[4][4],
            const uniform float camera2world[4][4],
            int x, int y, int length, Ray varying(LENGTH)&ray) {
    // transform raster coordinate (x, y, 0) to camera space
    float varying(LENGTH) camx = raster2camera[0][0] * x + raster2camera[0][1] * y + raster2camera[0][3];
    float varying(LENGTH) camy = raster2camera[1][0] * x + raster2camera[1][1] * y + raster2camera[1][3];
    float varying(LENGTH) camz = raster2camera[2][3];
    float varying(LENGTH) camw = raster2camera[3][3];
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


spmd(LENGTH)
static inline bool varying(LENGTH)
Inside(vec3 varying(LENGTH)& p, vec3 varying(LENGTH)& pMin, vec3 varying(LENGTH)& pMax) {
  bool varying(LENGTH) res = false;
  if (p.x >= pMin.x && p.x <= pMax.x &&
      p.y >= pMin.y && p.y <= pMax.y &&
      p.z >= pMin.z && p.z <= pMax.z)
    res = true;
  else
    res = false;
  return res;
}

spmd(LENGTH)
static float varying(LENGTH) void max(float varying(LENGTH)& x,
    float varying(LENGTH)& y)
{
  float varying(LENGTH)& res = 0;
  if ( x > y )
    res = x;
  else
    res = y;
  return res;
}

spmd(LENGTH)
static float varying(LENGTH) void min(float varying(LENGTH)& x,
    float varying(LENGTH)& y)
{
  float varying(LENGTH)& res = 0;
  if ( x < y )
    res = x;
  else
    res = y;
  return res;
}

static bool varying(LENGTH)
  IntersectP(const Ray &ray, vec3 varying(LENGTH)& pMin, vec3 varying(LENGTH)& pMax,
      float varying(LENGTH) *hit0, float varying(LENGTH) *hit1) {
    bool varying(LENGTH)& res = false;

    float varying(LENGTH) t0 = -1e30f;
    float varying(LENGTH) t1 = 1e30f;

      //float3 tNear = (pMin - ray.origin) / ray.dir;
    vec3 varying(LENGTH) tNear = div(sub(pMin, ray.origin), ray.dir);
    //float3 tFar  = (pMax - ray.origin) / ray.dir;
    vec3 varying(LENGTH) tFar = div(sub(pMax, ray.origin), ray.dir);
    if (tNear.x > tFar.x) {
        float varying(LENGTH) tmp = tNear.x;
        tNear.x = tFar.x;
        tFar.x = tmp;
    }
    //t0 = std::min(tNear.x, t0);
    t0 = max( tNear.x, t0 );
    //t1 = std::min(tFar.x, t1);
    t1 = max( tFar.x, t1 );

    if (tNear.y > tFar.y) {
        float tmp = tNear.y;
        tNear.y = tFar.y;
        tFar.y = tmp;
    }
    //t0 = std::max(tNear.y, t0);
    t0 = max( tNear.y, t0 );
    //t1 = std::min(tFar.y, t1);
    t1 = max( tFar.y, t1 );

    if (tNear.z > tFar.z) {
        float tmp = tNear.z;
        tNear.z = tFar.z;
        tFar.z = tmp;
    }
    //t0 = std::max(tNear.z, t0);
    t0 = max( tNear.z, t0 );
    //t1 = std::min(tFar.z, t1);
    t1 = max( tFar.z, t1 );
    
    if (t0 <= t1) {
        *hit0 = t0;
        *hit1 = t1;
        res = true;
    }
    else
      res = false;

    return res;
}


static inline float Lerp(float t, float a, float b) {
    return (1.f - t) * a + t * b;
}


static inline int Clamp(int v, int low, int high) {
    return std::min(std::max(v, low), high);
}


static inline float D(int x, int y, int z, int nVoxels[3], float density[]) {
    x = Clamp(x, 0, nVoxels[0]-1);
    y = Clamp(y, 0, nVoxels[1]-1);
    z = Clamp(z, 0, nVoxels[2]-1);
    return density[z*nVoxels[0]*nVoxels[1] + y*nVoxels[0] + x];
}


static inline float3 Offset(float3 p, float3 pMin, float3 pMax) {
    return float3((p.x - pMin.x) / (pMax.x - pMin.x),
                  (p.y - pMin.y) / (pMax.y - pMin.y),
                  (p.z - pMin.z) / (pMax.z - pMin.z));
}


static inline float Density(float3 Pobj, float3 pMin, float3 pMax, 
                            float density[], int nVoxels[3]) {
    if (!Inside(Pobj, pMin, pMax)) 
        return 0;
    // Compute voxel coordinates and offsets for _Pobj_
    float3 vox = Offset(Pobj, pMin, pMax);
    vox.x = vox.x * nVoxels[0] - .5f;
    vox.y = vox.y * nVoxels[1] - .5f;
    vox.z = vox.z * nVoxels[2] - .5f;
    int vx = (int)(vox.x), vy = (int)(vox.y), vz = (int)(vox.z);
    float dx = vox.x - vx, dy = vox.y - vy, dz = vox.z - vz;

    // Trilinearly interpolate density values to compute local density
    float d00 = Lerp(dx, D(vx, vy, vz, nVoxels, density),     
                         D(vx+1, vy, vz, nVoxels, density));
    float d10 = Lerp(dx, D(vx, vy+1, vz, nVoxels, density),   
                         D(vx+1, vy+1, vz, nVoxels, density));
    float d01 = Lerp(dx, D(vx, vy, vz+1, nVoxels, density),   
                         D(vx+1, vy, vz+1, nVoxels, density));
    float d11 = Lerp(dx, D(vx, vy+1, vz+1, nVoxels, density), 
                         D(vx+1, vy+1, vz+1, nVoxels, density));
    float d0 = Lerp(dy, d00, d10);
    float d1 = Lerp(dy, d01, d11);
    return Lerp(dz, d0, d1);
}



static float
transmittance(float3 p0, float3 p1, float3 pMin,
              float3 pMax, float sigma_t, float density[], int nVoxels[3]) {
    float rayT0, rayT1;
    Ray ray;
    ray.origin = p1;
    ray.dir = p0 - p1;

    // Find the parametric t range along the ray that is inside the volume.
    if (!IntersectP(ray, pMin, pMax, &rayT0, &rayT1))
        return 1.;

    rayT0 = std::max(rayT0, 0.f);

    // Accumulate beam transmittance in tau
    float tau = 0;
    float rayLength = sqrtf(ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y +
                            ray.dir.z * ray.dir.z);
    float stepDist = 0.2f;
    float stepT = stepDist / rayLength;

    float t = rayT0;
    float3 pos = ray.origin + ray.dir * rayT0;
    float3 dirStep = ray.dir * stepT;
    while (t < rayT1) {
        tau += stepDist * sigma_t * Density(pos, pMin, pMax, density, nVoxels);
        pos = pos + dirStep;
        t += stepT;
    }

    return expf(-tau);
}


static float
distanceSquared(float3 a, float3 b) {
    float3 d = a-b;
    return d.x*d.x + d.y*d.y + d.z*d.z;
}


static float 
raymarch(float density[], int nVoxels[3], const Ray &ray) {
    float rayT0, rayT1;
    float3 pMin(.3f, -.2f, .3f), pMax(1.8f, 2.3f, 1.8f);
    float3 lightPos(-1.f, 4.f, 1.5f);

    if (!IntersectP(ray, pMin, pMax, &rayT0, &rayT1))
        return 0.;

    rayT0 = std::max(rayT0, 0.f);

    // Parameters that define the volume scattering characteristics and
    // sampling rate for raymarching
    float Le = .25f;           // Emission coefficient
    float sigma_a = 10;        // Absorption coefficient
    float sigma_s = 10;        // Scattering coefficient
    float stepDist = 0.025f;   // Ray step amount
    float lightIntensity = 40; // Light source intensity

    float tau = 0.f;  // accumulated beam transmittance
    float L = 0;      // radiance along the ray
    float rayLength = sqrtf(ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y +
                            ray.dir.z * ray.dir.z);
    float stepT = stepDist / rayLength;

    float t = rayT0;
    float3 pos = ray.origin + ray.dir * rayT0;
    float3 dirStep = ray.dir * stepT;
    while (t < rayT1) {
        float d = Density(pos, pMin, pMax, density, nVoxels);

        // terminate once attenuation is high
        float atten = expf(-tau);
        if (atten < .005f)
            break;

        // direct lighting
        float Li = lightIntensity / distanceSquared(lightPos, pos) * 
            transmittance(lightPos, pos, pMin, pMax, sigma_a + sigma_s,
                          density, nVoxels);
        L += stepDist * atten * d * sigma_s * (Li + Le);

        // update beam transmittance
        tau += stepDist * (sigma_a + sigma_s) * d;

        pos = pos + dirStep;
        t += stepT;
    }

    // Gamma correction
    return powf(L, 1.f / 2.2f);
}


void
volume_sierra(float density[], int nVoxels[3], const float raster2camera[4][4],
              const float camera2world[4][4], 
              int width, int height, float image[]) {
    int offset = 0;
    int length = std::sqrt( LENGTH );
    int index = 0;
    const uniform int xoffsets[16] = { 0, 1, 0, 1, 2, 3, 2, 3,
      0, 1, 0, 1, 2, 3, 2, 3 };
    const uniform int yoffsets[16] = { 0, 0, 1, 1, 0, 0, 1, 1,
      2, 2, 3, 3, 2, 2, 3, 3 };

    for (int y = 0; y < height; y += length) {
        for (int x = 0; x < width; x += length) {
          Ray varying(LENGTH) ray;
          generateRay(raster2camera, camera2world, x, y, length, ray);
          // TODO extract vector generated by raymarch, and write it to the
          // image buffer
          raymarch(density, nVoxels, ray);
        }
    }
}
