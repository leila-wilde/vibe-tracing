#include "../src/material.h"
#include "../src/hittable.h"
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

/* Build a hit_record facing the given normal */
static hit_record_t make_rec(vec3_t normal) {
    hit_record_t rec = {0};
    rec.point = vec3(0.0, 0.0, 0.0);
    rec.normal = normal;
    rec.front_face = 1;
    rec.t = 1.0;
    return rec;
}

int main(void) {
    /* --- Lambertian --- */
    vec3_t albedo = vec3(0.8, 0.3, 0.1);
    material_t lamb = lambertian_create(albedo);

    ray_t r_in = ray(vec3(0.0, 1.0, 0.0), vec3(0.0, -1.0, 0.0));
    hit_record_t rec = make_rec(vec3(0.0, 1.0, 0.0));
    rec.material = &lamb;

    ray_t scattered = {0};
    vec3_t attenuation = {0};

    int did_scatter = lamb.scatter(lamb.data, r_in, &rec, &attenuation, &scattered);
    check("lambertian scatter returns 1", did_scatter == 1);
    /* Attenuation equals albedo */
    check("lambertian attenuation.r", fabs(attenuation.e[0] - albedo.e[0]) < EPSILON);
    check("lambertian attenuation.g", fabs(attenuation.e[1] - albedo.e[1]) < EPSILON);
    check("lambertian attenuation.b", fabs(attenuation.e[2] - albedo.e[2]) < EPSILON);

    if (lamb.destroy) lamb.destroy(lamb.data);

    /* --- Metal --- */
    vec3_t metal_albedo = vec3(0.9, 0.9, 0.9);
    material_t met = metal_create(metal_albedo, 0.0);

    /* Incoming ray from above, surface normal up: reflected ray goes up */
    ray_t r_down = ray(vec3(0.0, 1.0, 0.0), vec3(0.0, -1.0, 0.0));
    hit_record_t rec_m = make_rec(vec3(0.0, 1.0, 0.0));
    rec_m.material = &met;

    ray_t scattered_m = {0};
    vec3_t attenuation_m = {0};
    int metal_scatter = met.scatter(met.data, r_down, &rec_m, &attenuation_m, &scattered_m);
    check("metal scatter returns 1", metal_scatter == 1);
    /* Reflected ray should go upward (positive y) with no fuzz */
    check("metal reflection goes up", scattered_m.direction.e[1] > 0.0);

    if (met.destroy) met.destroy(met.data);

    /* --- Dielectric --- */
    material_t glass = dielectric_create(1.5);

    ray_t r_glass = ray(vec3(0.0, 1.0, 0.0), vec3(0.0, -1.0, 0.0));
    hit_record_t rec_g = make_rec(vec3(0.0, 1.0, 0.0));
    rec_g.material = &glass;

    ray_t scattered_g = {0};
    vec3_t attenuation_g = {0};
    int glass_scatter = glass.scatter(glass.data, r_glass, &rec_g, &attenuation_g, &scattered_g);
    check("dielectric scatter returns 1", glass_scatter == 1);
    /* Glass attenuation is always (1,1,1) */
    check("dielectric attenuation is white",
          fabs(attenuation_g.e[0] - 1.0) < EPSILON &&
          fabs(attenuation_g.e[1] - 1.0) < EPSILON &&
          fabs(attenuation_g.e[2] - 1.0) < EPSILON);

    if (glass.destroy) glass.destroy(glass.data);

    printf("\n%d/%d tests passed\n", passed, passed + failed);
    return failed == 0 ? 0 : 1;
}
