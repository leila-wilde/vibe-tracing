#include "../src/sphere.h"
#include "../src/hittable.h"
#include "../src/material.h"
#include "../src/vec3.h"
#include "../src/ray.h"
#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6

static int passed = 0, failed = 0;

static void check(const char *name, int condition) {
    if (condition) {
        printf("✓ %s\n", name);
        passed++;
    } else {
        printf("✗ %s\n", name);
        failed++;
    }
}

static void check_double(const char *name, double got, double exp) {
    if (fabs(got - exp) < EPSILON) {
        printf("✓ %s\n", name);
        passed++;
    } else {
        printf("✗ %s (got %f expected %f)\n", name, got, exp);
        failed++;
    }
}

static void check_vec3(const char *name, vec3_t got, vec3_t exp) {
    if (fabs(got.e[0] - exp.e[0]) < EPSILON &&
        fabs(got.e[1] - exp.e[1]) < EPSILON &&
        fabs(got.e[2] - exp.e[2]) < EPSILON) {
        printf("✓ %s\n", name);
        passed++;
    } else {
        printf("✗ %s (got [%f,%f,%f] expected [%f,%f,%f])\n",
               name, got.e[0], got.e[1], got.e[2],
               exp.e[0], exp.e[1], exp.e[2]);
        failed++;
    }
}

int main(void) {
    material_t dummy_mat = {0};

    /* Ray pointing straight at sphere at origin */
    sphere_t *s = sphere_create(vec3(0.0, 0.0, -1.0), 0.5, &dummy_mat);
    hittable_t h = sphere_to_hittable(s);

    ray_t r_hit = ray(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, -1.0));
    hit_record_t rec = {0};

    /* Direct hit */
    check("sphere hit returns 1", h.hit(h.data, r_hit, 0.001, 1e9, &rec));
    check_double("sphere hit t ~ 0.5", rec.t, 0.5);
    check_vec3("sphere hit point", rec.point, vec3(0.0, 0.0, -0.5));

    /* Front-face normal points toward ray origin */
    check("front face detected", rec.front_face == 1);
    check_vec3("outward normal", rec.normal, vec3(0.0, 0.0, 1.0));

    /* Ray going perpendicular — misses */
    ray_t r_miss = ray(vec3(0.0, 2.0, 0.0), vec3(0.0, 0.0, -1.0));
    hit_record_t rec2 = {0};
    check("sphere miss returns 0", !h.hit(h.data, r_miss, 0.001, 1e9, &rec2));

    /* Ray starting inside sphere — hits back wall, back-face normal */
    ray_t r_inside = ray(vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, -1.0));
    hit_record_t rec3 = {0};
    check("inside sphere hit returns 1", h.hit(h.data, r_inside, 0.001, 1e9, &rec3));
    check("inside sphere back face", rec3.front_face == 0);

    /* t_max culling: t=0.5 hit is beyond t_max=0.4 */
    hit_record_t rec4 = {0};
    check("t_max culls hit", !h.hit(h.data, r_hit, 0.001, 0.4, &rec4));

    h.destroy(h.data);

    printf("\n%d/%d tests passed\n", passed, passed + failed);
    return failed == 0 ? 0 : 1;
}
