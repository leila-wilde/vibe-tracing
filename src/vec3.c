#include "vec3.h"
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#endif

/* Thread-local random state, lazily initialized per thread */
static __thread unsigned int seed = 0;

/* Construct a vec3 from three doubles */
inline vec3_t vec3(double x, double y, double z) {
    return (vec3_t){{x, y, z}};
}

/* Add two vectors */
inline vec3_t vec3_add(const vec3_t a, const vec3_t b) {
    return vec3(a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2]);
}

/* Subtract two vectors */
inline vec3_t vec3_sub(const vec3_t a, const vec3_t b) {
    return vec3(a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2]);
}

/* Multiply vector by scalar */
inline vec3_t vec3_mul(const vec3_t v, double t) {
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

/* Divide vector by scalar */
inline vec3_t vec3_div(const vec3_t v, double t) {
    return vec3_mul(v, 1.0 / t);
}

/* Dot product */
inline double vec3_dot(const vec3_t a, const vec3_t b) {
    return a.e[0] * b.e[0] + a.e[1] * b.e[1] + a.e[2] * b.e[2];
}

/* Cross product */
inline vec3_t vec3_cross(const vec3_t a, const vec3_t b) {
    return vec3(a.e[1] * b.e[2] - a.e[2] * b.e[1],
                a.e[2] * b.e[0] - a.e[0] * b.e[2],
                a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}

/* Length (magnitude) of vector */
inline double vec3_length(const vec3_t v) {
    return sqrt(vec3_length_squared(v));
}

/* Length squared (avoid sqrt when possible) */
inline double vec3_length_squared(const vec3_t v) {
    return vec3_dot(v, v);
}

/* Unit vector (normalized) */
inline vec3_t vec3_normalize(const vec3_t v) {
    return vec3_div(v, vec3_length(v));
}

/* Generate random double in [0, 1) */
double random_double(void) {
    if (!seed) {
        /* Give each thread a unique starting seed using Knuth's
         * multiplicative hash on thread id so samples don't correlate */
#ifdef _OPENMP
        seed = (unsigned int)(omp_get_thread_num() + 1) * 0x9e3779b9u;
#else
        seed = 12345u;
#endif
        if (!seed) seed = 1u; /* rand_r is undefined for seed==0 */
    }
    return rand_r(&seed) / (RAND_MAX + 1.0);
}

/* Generate random double in [min, max) */
double random_double_range(double min, double max) {
    return min + (max - min) * random_double();
}

/* Generate random vec3 with components in [0, 1) */
vec3_t random_vec3(void) {
    return vec3(random_double(), random_double(), random_double());
}

/* Generate random vec3 with components in [min, max) */
vec3_t random_vec3_range(double min, double max) {
    return vec3(random_double_range(min, max),
                random_double_range(min, max),
                random_double_range(min, max));
}

/* Generate random unit vector using rejection sampling */
vec3_t random_unit_vector(void) {
    while (1) {
        vec3_t p = random_vec3_range(-1.0, 1.0);
        double len_sq = vec3_length_squared(p);
        if (len_sq >= 1e-160 && len_sq <= 1.0) {
            return vec3_normalize(p);
        }
    }
}

/* Generate random vector in unit sphere using rejection sampling */
vec3_t random_in_unit_sphere(void) {
    while (1) {
        vec3_t p = random_vec3_range(-1.0, 1.0);
        if (vec3_length_squared(p) <= 1.0) {
            return p;
        }
    }
}
