#include "ray.h"

/* Construct a ray from origin and direction */
ray_t ray(const vec3_t origin, const vec3_t direction) {
    return (ray_t){origin, direction};
}

/* Get point at parameter t along the ray */
vec3_t ray_at(const ray_t r, double t) {
    return vec3_add(r.origin, vec3_mul(r.direction, t));
}
