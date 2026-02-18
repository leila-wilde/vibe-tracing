#include "camera.h"
#include "vec3.h"
#include <math.h>

#define PI 3.1415926535897932385

/* Random point in unit disk for defocus blur */
static vec3_t random_in_unit_disk(void) {
    while (1) {
        vec3_t p = vec3(random_double_range(-1.0, 1.0),
                        random_double_range(-1.0, 1.0), 0.0);
        if (vec3_length_squared(p) <= 1.0) {
            return p;
        }
    }
}

/* Create a camera with look-at and field of view */
camera_t camera_create(vec3_t lookfrom, vec3_t lookat, vec3_t vup, double vfov,
                       double aspect_ratio, double aperture, double focus_dist) {
    double theta = vfov * PI / 180.0;
    double h = tan(theta / 2.0);
    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    vec3_t w = vec3_normalize(vec3_sub(lookfrom, lookat));
    vec3_t u = vec3_normalize(vec3_cross(vup, w));
    vec3_t v = vec3_cross(w, u);

    vec3_t horizontal = vec3_mul(u, viewport_width * focus_dist);
    vec3_t vertical = vec3_mul(v, viewport_height * focus_dist);
    vec3_t lower_left = vec3_sub(
        vec3_sub(vec3_sub(lookfrom, vec3_mul(horizontal, 0.5)),
                 vec3_mul(vertical, 0.5)),
        vec3_mul(w, focus_dist));

    double lens_radius = aperture / 2.0;

    return (camera_t){
        .origin = lookfrom,
        .lower_left_corner = lower_left,
        .horizontal = horizontal,
        .vertical = vertical,
        .u = u,
        .v = v,
        .w = w,
        .lens_radius = lens_radius,
    };
}

/* Generate a ray through the camera at (u, v) with optional random offset */
ray_t camera_get_ray(const camera_t *cam, double u, double v) {
    vec3_t rd = vec3_mul(random_in_unit_disk(), cam->lens_radius);
    vec3_t offset = vec3_add(vec3_mul(cam->u, rd.e[0]),
                              vec3_mul(cam->v, rd.e[1]));

    return ray(
        vec3_add(cam->origin, offset),
        vec3_sub(vec3_add(cam->lower_left_corner,
                         vec3_add(vec3_mul(cam->horizontal, u),
                                 vec3_mul(cam->vertical, v))),
                vec3_add(cam->origin, offset)));
}
