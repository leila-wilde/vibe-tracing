#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/* Ray structure: P(t) = A + t*B where A is origin, B is direction */
typedef struct {
    vec3_t origin;
    vec3_t direction;
} ray_t;

/* Construct a ray from origin and direction */
ray_t ray(const vec3_t origin, const vec3_t direction);

/* Get point at parameter t along the ray */
vec3_t ray_at(const ray_t r, double t);

#endif /* RAY_H */
