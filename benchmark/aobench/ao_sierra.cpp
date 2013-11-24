// -*- mode: c++ -*-
/*
  Copyright (c) 2010-2011, Intel Corporation
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
/*
  Based on Syoyo Fujita's aobench: http://code.google.com/p/aobench
*/

#define NAO_SAMPLES		8
#define M_PI 3.1415926535f

#define LENGTH 4
#define L LENGTH
#include "sierra/vec3.h"

using namespace sierra;

struct Isect {
    float      t;
    vec3       p;
    vec3       n;
    int        hit; 
};

struct Sphere {
    vec3       center;
    float      radius;
};

struct Plane {
    vec3    p;
    vec3    n;
};

struct Ray {
    vec3 org;
    vec3 dir;
};

static spmd(L)
void ray_plane_intersect(Isect varying(L)& isect, Ray varying(L)& ray, Plane uniform& plane) {
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
        }
    }
}

static spmd(L)
void ray_sphere_intersect(Isect varying(L)& isect, Ray varying(L)& ray, Sphere uniform& sphere) {
    vec3 varying(L) sphere_center;
    splat(sphere_center, sphere.center);

    //vec3 rs = ray.org - sphere.center;
    vec3 varying(L) rs;
    sub(rs, ray.org, sphere_center);

    float varying(L) B = dot(rs, ray.dir);
    float varying(L) C = dot(rs, rs) - sphere.radius * sphere.radius;
    float varying(L) D = B * B - C;

    if (D > 0.) {
        float varying(L) t = -B - sqrt(D);

        if ((t > 0.0) && (t < isect.t)) {
            isect.t = t;
            isect.hit = 1;
            //isect.p = ray.org + t * ray.dir;
            fma(isect.p, t, ray.dir, ray.org);
            //isect.n = isect.p - sphere.center;
            sub(isect.n, isect.p, sphere_center);
            normalize(isect.n);
        }
    }
}

static spmd(L)
void orthoBasis(vec3 varying(L) basis[3], vec3 varying(L) n) {
    // TODO
    basis[2] = n;
    basis[1].x = 0.0; basis[1].y = 0.0; basis[1].z = 0.0;

    if ((n.x < 0.6) && (n.x > -0.6)) {
        basis[1].x = 1.0;
    } else if ((n.y < 0.6) && (n.y > -0.6)) {
        basis[1].y = 1.0;
    } else if ((n.z < 0.6) && (n.z > -0.6)) {
        basis[1].z = 1.0;
    } else {
        basis[1].x = 1.0;
    }

    basis[0] = vcross(basis[1], basis[2]);
    vnormalize(basis[0]);

    basis[1] = vcross(basis[2], basis[0]);
    vnormalize(basis[1]);
}


static float
ambient_occlusion(Isect &isect, uniform Plane &plane, uniform Sphere spheres[3],
                  RNGState &rngstate) {
    float eps = 0.0001f;
    vec3 p, n;
    vec3 basis[3];
    float occlusion = 0.0;

    p = isect.p + eps * isect.n;

    orthoBasis(basis, isect.n);

    static const uniform int ntheta = NAO_SAMPLES;
    static const uniform int nphi   = NAO_SAMPLES;
    for (uniform int j = 0; j < ntheta; j++) {
        for (uniform int i = 0; i < nphi; i++) {
            Ray ray;
            Isect occIsect;

            float theta = sqrt(frandom(&rngstate));
            float phi   = 2.0f * M_PI * frandom(&rngstate);
            float x = cos(phi) * theta;
            float y = sin(phi) * theta;
            float z = sqrt(1.0 - theta * theta);

            // local . global
            float rx = x * basis[0].x + y * basis[1].x + z * basis[2].x;
            float ry = x * basis[0].y + y * basis[1].y + z * basis[2].y;
            float rz = x * basis[0].z + y * basis[1].z + z * basis[2].z;

            ray.org = p;
            ray.dir.x = rx;
            ray.dir.y = ry;
            ray.dir.z = rz;

            occIsect.t   = 1.0e+17;
            occIsect.hit = 0;

            for (uniform int snum = 0; snum < 3; ++snum)
                ray_sphere_intersect(occIsect, ray, spheres[snum]); 
            ray_plane_intersect (occIsect, ray, plane); 

            if (occIsect.hit) occlusion += 1.0;
        }
    }

    occlusion = (ntheta * nphi - occlusion) / (float)(ntheta * nphi);
    return occlusion;
}


/* Compute the image for the scanlines from [y0,y1), for an overall image
   of width w and height h.
 */
static void ao_scanlines(uniform int y0, uniform int y1, uniform int w, 
                         uniform int h,  uniform int nsubsamples, 
                         uniform float image[]) {
    static uniform Plane plane = { { 0.0f, -0.5f, 0.0f }, { 0.f, 1.f, 0.f } };
    static uniform Sphere spheres[3] = {
        { { -2.0f, 0.0f, -3.5f }, 0.5f },
        { { -0.5f, 0.0f, -3.0f }, 0.5f },
        { { 1.0f, 0.0f, -2.2f }, 0.5f } };
    RNGState rngstate;

    seed_rng(&rngstate, programIndex + (y0 << (programIndex & 15)));
    float invSamples = 1.f / nsubsamples;

    foreach_tiled(y = y0 ... y1, x = 0 ... w, 
                  u = 0 ... nsubsamples, v = 0 ... nsubsamples) {
        float du = (float)u * invSamples, dv = (float)v * invSamples;

        // Figure out x,y pixel in NDC
        float px =  (x + du - (w / 2.0f)) / (w / 2.0f);
        float py = -(y + dv - (h / 2.0f)) / (h / 2.0f);
        float ret = 0.f;
        Ray ray;
        Isect isect;

        ray.org = 0.f;

        // Poor man's perspective projection
        ray.dir.x = px;
        ray.dir.y = py;
        ray.dir.z = -1.0;
        vnormalize(ray.dir);

        isect.t   = 1.0e+17;
        isect.hit = 0;

        for (uniform int snum = 0; snum < 3; ++snum)
            ray_sphere_intersect(isect, ray, spheres[snum]);
        ray_plane_intersect(isect, ray, plane);

        // Note use of 'coherent' if statement; the set of rays we
        // trace will often all hit or all miss the scene
        cif (isect.hit) {
            ret = ambient_occlusion(isect, plane, spheres, rngstate);
            ret *= invSamples * invSamples;

            int offset = 3 * (y * w + x);
            atomic_add_local(&image[offset], ret);
            atomic_add_local(&image[offset+1], ret);
            atomic_add_local(&image[offset+2], ret);
        }
    }
}


export void ao_ispc(uniform int w, uniform int h, uniform int nsubsamples, 
                    uniform float image[]) {
    ao_scanlines(0, h, w, h, nsubsamples, image);
}


static void task ao_task(uniform int width, uniform int height, 
                         uniform int nsubsamples, uniform float image[]) {
    ao_scanlines(taskIndex, taskIndex+1, width, height, nsubsamples, image);
}


export void ao_ispc_tasks(uniform int w, uniform int h, uniform int nsubsamples, 
                          uniform float image[]) {
    launch[h] ao_task(w, h, nsubsamples, image);
}
