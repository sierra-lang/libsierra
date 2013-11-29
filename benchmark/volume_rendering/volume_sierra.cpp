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

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <math.h>

#include "../../sierra/sierra.h"
#define L LENGTH
#include "../../sierra/math.h"
#include "../../sierra/vec3.h"
#undef L

using namespace sierra;

template< int L >
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
  vec3 origin, dir;
};


static void
generateRay(const float raster2camera[4][4],
    const float camera2world[4][4],
    int const varying(LENGTH) x, int const varying(LENGTH) y,
    Ray varying(LENGTH)& ray) {

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
  Inside(vec3 const varying(LENGTH)& p,
      vec3 const varying(LENGTH)& pMin,
      vec3 const varying(LENGTH)& pMax) {
    bool varying(LENGTH) res = false;

    if (p.x >= pMin.x && p.x <= pMax.x &&
        p.y >= pMin.y && p.y <= pMax.y &&
        p.z >= pMin.z && p.z <= pMax.z)
      res = true;

    return res;
  }

  spmd(LENGTH)
static bool varying(LENGTH)
  IntersectP(const Ray varying(LENGTH)& ray,
      vec3 varying(LENGTH)& pMin, vec3 varying(LENGTH)& pMax,
      float varying(LENGTH) *hit0, float varying(LENGTH) *hit1) {
    bool varying(LENGTH) res = false;

    float varying(LENGTH) t0 = -1e30f;
    float varying(LENGTH) t1 = 1e30f;

    //float3 tNear = (pMin - ray.origin) / ray.dir;
    vec3 varying(LENGTH) tNear;
    sierra::copy( tNear, pMin );
    sierra::sub_assign( tNear, ray.origin );
    sierra::div_assign( tNear, ray.dir );
    //float3 tFar  = (pMax - ray.origin) / ray.dir;
    vec3 varying(LENGTH) tFar;
    sierra::copy( tFar, pMax );
    sierra::sub_assign( tFar, ray.origin );
    sierra::div_assign( tFar, ray.dir );

    if (tNear.x > tFar.x) {
      float const varying(LENGTH) tmp = tNear.x;
      tNear.x = tFar.x;
      tFar.x = tmp;
    }
    //t0 = max(tNear.x, t0);
    t0 = sierra::fmax( tNear.x, t0 );
    //t1 = min(tFar.x, t1);
    t1 = sierra::fmin( tFar.x, t1 );

    if (tNear.y > tFar.y) {
      float const varying(LENGTH) tmp = tNear.y;
      tNear.y = tFar.y;
      tFar.y = tmp;
    }
    //t0 = max(tNear.y, t0);
    t0 = sierra::fmax( tNear.y, t0 );
    //t1 = min(tFar.y, t1);
    t1 = sierra::fmin( tFar.y, t1 );

    if (tNear.z > tFar.z) {
      float const varying(LENGTH) tmp = tNear.z;
      tNear.z = tFar.z;
      tFar.z = tmp;
    }
    //t0 = max(tNear.z, t0);
    t0 = sierra::fmax( tNear.z, t0 );
    //t1 = min(tFar.z, t1);
    t1 = sierra::fmin( tFar.z, t1 );

    if (t0 <= t1) {
      *hit0 = t0;
      *hit1 = t1;
      res = true;
    }
    else
      res = false;

    return res;
  }


  spmd(LENGTH)
static inline float varying(LENGTH)
  Lerp(float varying(LENGTH) t, float varying(LENGTH) a, float varying(LENGTH) b) {
    return (1.f - t) * a + t * b;
  }


  spmd(LENGTH)
static inline int varying(LENGTH)
  Clamp(int varying(LENGTH) v, int varying(LENGTH) low,
      int varying(LENGTH) high) {
    return sierra::imin(sierra::imax(v, low), high);
  }


  spmd(LENGTH)
static inline float varying(LENGTH)
  D(int varying(LENGTH) x, int varying(LENGTH) y, int varying(LENGTH) z,
      int nVoxels[3], float density[]) {
    x = Clamp(x, 0, nVoxels[0]-1);
    y = Clamp(y, 0, nVoxels[1]-1);
    z = Clamp(z, 0, nVoxels[2]-1);

    // Gather
    //return density[z*nVoxels[0]*nVoxels[1] + y*nVoxels[0] + x];
    float varying(LENGTH) res;
    for ( int i = 0; i < LENGTH; ++i )
      sierra::insert( res, i, density[
          sierra::extract( z, i ) * nVoxels[0] * nVoxels[1]
          + sierra::extract( y, i ) * nVoxels[0]
          + sierra::extract( x, i ) ] );
    return res;
  }


//static inline float3 Offset(float3 p, float3 pMin, float3 pMax) {
//return float3((p.x - pMin.x) / (pMax.x - pMin.x),
//(p.y - pMin.y) / (pMax.y - pMin.y),
//(p.z - pMin.z) / (pMax.z - pMin.z));
//}

  spmd(LENGTH)
static inline void Offset( vec3 varying(LENGTH)& res,
    vec3 const varying(LENGTH)& p,
    vec3 const varying(LENGTH)& pMin,
    vec3 const varying(LENGTH)& pMax )
{
  vec3 varying(LENGTH) tmp;
  sierra::copy( tmp, pMax );
  sierra::sub_assign( tmp, pMin ); // pMax - pMin
  sierra::copy( res, p );
  sierra::sub_assign( res, pMin ); // p - pMin
  sierra::div_assign( res, tmp ); // (p - pMin) / (pMax - pMin)
}

  spmd(LENGTH)
static inline float varying(LENGTH)
  Density(vec3 varying(LENGTH)& Pobj, vec3 varying(LENGTH)& pMin,
      vec3 varying(LENGTH)& pMax, float density[], int nVoxels[3]) {
    float varying(LENGTH) res = 0;

    if (Inside(Pobj, pMin, pMax)) 
    {
      // Compute voxel coordinates and offsets for _Pobj_
      //float3 vox = Offset(Pobj, pMin, pMax);
      vec3 varying(LENGTH) vox;
      Offset( vox, Pobj, pMin, pMax ); // init vox
      vox.x = vox.x * nVoxels[0] - .5f;
      vox.y = vox.y * nVoxels[1] - .5f;
      vox.z = vox.z * nVoxels[2] - .5f;
      int varying(LENGTH) vx = (int varying(LENGTH))(vox.x);
      int varying(LENGTH) vy = (int varying(LENGTH))(vox.y);
      int varying(LENGTH) vz = (int varying(LENGTH))(vox.z);
      float varying(LENGTH) dx = vox.x - vx, dy = vox.y - vy, dz = vox.z - vz;

      // Trilinearly interpolate density values to compute local density
      float varying(LENGTH) d00 = Lerp(dx, D(vx, vy, vz, nVoxels, density),     
          D(vx+1, vy, vz, nVoxels, density));
      float varying(LENGTH) d10 = Lerp(dx, D(vx, vy+1, vz, nVoxels, density),   
          D(vx+1, vy+1, vz, nVoxels, density));
      float varying(LENGTH) d01 = Lerp(dx, D(vx, vy, vz+1, nVoxels, density),   
          D(vx+1, vy, vz+1, nVoxels, density));
      float varying(LENGTH) d11 = Lerp(dx, D(vx, vy+1, vz+1, nVoxels, density), 
          D(vx+1, vy+1, vz+1, nVoxels, density));
      float varying(LENGTH) d0 = Lerp(dy, d00, d10);
      float varying(LENGTH) d1 = Lerp(dy, d01, d11);
      res = Lerp(dz, d0, d1);
    }
    return res;
  }


  spmd(LENGTH)
  static float varying(LENGTH)
transmittance(vec3 varying(LENGTH)& p0, vec3 varying(LENGTH)& p1,
    vec3 varying(LENGTH)& pMin, vec3 varying(LENGTH)& pMax,
    float const sigma_t, float density[], int nVoxels[3])
{
  float varying(LENGTH) rayT0;
  float varying(LENGTH) rayT1;

  Ray varying(LENGTH) ray;
  //ray.origin = p1;
  sierra::copy( ray.origin, p1 );
  //ray.dir = p0 - p1;
  sierra::copy( ray.dir, p0 );
  sierra::sub_assign( ray.dir, p1 ); // p0 - p1

  float varying(LENGTH) res = 1.f;

  // Find the parametric t range along the ray that is inside the volume.
  if (IntersectP(ray, pMin, pMax, &rayT0, &rayT1))
  {
    rayT0 = sierra::fmax(rayT0, 0.f);

    // Accumulate beam transmittance in tau
    float varying(LENGTH) tau = 0;
    float varying(LENGTH) rayLength = sierra::sqrt(ray.dir.x * ray.dir.x
        + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z);
    float const stepDist = 0.2f;
    float varying(LENGTH) stepT = stepDist / rayLength;

    float varying(LENGTH) t = rayT0;
    //float3 pos = ray.origin + ray.dir * rayT0;
    vec3 varying(LENGTH) pos;
    sierra::copy( pos, ray.dir );
    sierra::mul_assign( pos, rayT0 );
    sierra::add_assign( pos, ray.origin );
    //float3 dirStep = ray.dir * stepT;
    vec3 varying(LENGTH) dirStep;
    sierra::copy( dirStep, ray.dir );
    sierra::mul_assign( dirStep, stepT );
    while (t < rayT1) {
      tau += stepDist * sigma_t * Density(pos, pMin, pMax, density, nVoxels);
      //pos = pos + dirStep;
      sierra::add_assign( pos, dirStep );
      t += stepT;
    }
    res = sierra::exp(-tau);
  }

  return res;
}


  spmd(LENGTH)
static float varying(LENGTH)
  distanceSquared(vec3 varying(LENGTH)& a, vec3 varying(LENGTH)& b) {
    //float3 d = a-b;
    //return d.x*d.x + d.y*d.y + d.z*d.z;
    vec3 varying(LENGTH) d;
    sierra::copy( d, a );
    sierra::sub_assign( d, b );
    return d.x*d.x + d.y*d.y + d.z*d.z;
  }


static float varying(LENGTH)
  raymarch(float density[], int nVoxels[3], const Ray varying(LENGTH)& ray) {
    float varying(LENGTH) res = 0;

    float varying(LENGTH) rayT0;
    float varying(LENGTH) rayT1;

    //float3 pMin(.3f, -.2f, .3f), pMax(1.8f, 2.3f, 1.8f);
    vec3 varying(LENGTH) pMin;
    pMin.x = .3f;
    pMin.y = -.2f;
    pMin.z = .3f;

    vec3 varying(LENGTH) pMax;
    pMax.x = 1.8f;
    pMax.y = 2.3f;
    pMax.z = 1.8f;

    //float3 lightPos(-1.f, 4.f, 1.5f);
    vec3 varying(LENGTH) lightPos;
    lightPos.x = -1.f;
    lightPos.y = 4.f;
    lightPos.z = 1.5f;

    spmd_mode(LENGTH)
    {
      if (IntersectP(ray, pMin, pMax, &rayT0, &rayT1))
      {
        rayT0 = sierra::fmax(rayT0, 0.f);

        // Parameters that define the volume scattering characteristics and
        // sampling rate for raymarching
        float const Le = .25f;           // Emission coefficient
        float const sigma_a = 10;        // Absorption coefficient
        float const sigma_s = 10;        // Scattering coefficient
        float const stepDist = 0.025f;   // Ray step amount
        float const lightIntensity = 40; // Light source intensity

        float varying(LENGTH) tau = 0.f;  // accumulated beam transmittance
        float varying(LENGTH) L = 0.f;      // radiance along the ray
        float varying(LENGTH) rayLength = sierra::sqrt(ray.dir.x * ray.dir.x
            + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z);
        float varying(LENGTH) stepT = stepDist / rayLength;

        float varying(LENGTH) t = rayT0;

        //float3 pos = ray.dir * rayT0 + ray.origin;
        vec3 varying(LENGTH) pos;
        sierra::copy( pos, ray.dir );
        sierra::mul_assign( pos, rayT0 );
        sierra::add_assign( pos, ray.origin );
        //float3 dirStep = ray.dir * stepT;
        vec3 varying(LENGTH) dirStep;
        sierra::copy( pos, ray.dir );
        sierra::mul_assign( pos, stepT );

        bool varying(LENGTH) attenMask = true;
        while (attenMask && t < rayT1) {
          float varying(LENGTH) d = Density(pos, pMin, pMax, density, nVoxels);

          // terminate once attenuation is high
          float varying(LENGTH) atten = sierra::exp(-tau);
          if (atten < .005f)
          {
            attenMask = false;
          }
          else
          {

            // direct lighting
            float varying(LENGTH) Li = lightIntensity / distanceSquared(lightPos, pos) * 
              transmittance(lightPos, pos, pMin, pMax, sigma_a + sigma_s,
                  density, nVoxels);
            L += stepDist * atten * d * sigma_s * (Li + Le);

            // update beam transmittance
            tau += stepDist * (sigma_a + sigma_s) * d;

            //pos = pos + dirStep;
            sierra::add_assign( pos, dirStep );
            t += stepT;
          } // end if atten
        } // end while
        // Gamma correction
        res = sierra::pow(L, 1.f / 2.2f);
      } // end if intersectP
    }
    return res;
  }


void
volume_sierra(float density[], int nVoxels[3], const float raster2camera[4][4],
    const float camera2world[4][4], 
    int width, int height, float image[]) {
  int offset = 0;
  int index = 0;
  const int xoffsets[16] = { 0, 1, 0, 1, 2, 3, 2, 3,
    0, 1, 0, 1, 2, 3, 2, 3 };
  const int yoffsets[16] = { 0, 0, 1, 1, 0, 0, 1, 1,
    2, 2, 3, 3, 2, 2, 3, 3 };

  int const varying(LENGTH) *offsetPtr;

  for (int y = 0; y < height; y += LSQRT<LENGTH>::y) {
    for (int x = 0; x < width; x += LSQRT<LENGTH>::x) {
      Ray varying(LENGTH) ray;

      offsetPtr = (int varying(LENGTH) *) xoffsets;
      float const varying(LENGTH) xo = (float) x + *offsetPtr;
      offsetPtr = (int varying(LENGTH) *) yoffsets;
      float const varying(LENGTH) yo = (float) y + *offsetPtr;

      generateRay(raster2camera, camera2world, xo, yo, ray);
      float varying(LENGTH) res = raymarch(density, nVoxels, ray);

      int offset = y * width + x;
      // extract vector generated by raymarch, and write it to the
      for ( int off = 0; off < LENGTH; ++off )
        image[offset + yoffsets[off] * width + xoffsets[off]]
          = sierra::extract( res, off );
    }
  }
}
