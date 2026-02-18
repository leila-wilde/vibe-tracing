#include "../src/camera.h"
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
        printf("✗ %s (got %.8f expected %.8f)\n", name, got, exp);
        failed++;
    }
}

int main(void) {
    /* Simple camera looking straight down -Z with no aperture */
    camera_t cam = camera_create(
        vec3(0.0, 0.0, 0.0),   /* lookfrom */
        vec3(0.0, 0.0, -1.0),  /* lookat */
        vec3(0.0, 1.0, 0.0),   /* vup */
        90.0,                   /* vfov */
        1.0,                    /* aspect ratio (square) */
        0.0,                    /* aperture = 0 (no blur) */
        1.0                     /* focus distance */
    );

    /* Origin should be at (0,0,0) */
    check("camera origin x", fabs(cam.origin.e[0]) < EPSILON);
    check("camera origin y", fabs(cam.origin.e[1]) < EPSILON);
    check("camera origin z", fabs(cam.origin.e[2]) < EPSILON);

    /* Lens radius = aperture / 2 = 0 */
    check_double("lens radius = 0", cam.lens_radius, 0.0);

    /* Ray through image center (u=0.5, v=0.5) should point toward -Z */
    ray_t center_ray = camera_get_ray(&cam, 0.5, 0.5);
    /* Origin should be (0,0,0) when no aperture */
    check("center ray origin x ~ 0", fabs(center_ray.origin.e[0]) < EPSILON);
    check("center ray origin z ~ 0", fabs(center_ray.origin.e[2]) < EPSILON);
    /* Direction should point in -Z direction */
    check("center ray goes toward -Z", center_ray.direction.e[2] < 0.0);

    /* Ray through top-right (u=1, v=1) should have positive x and y in direction */
    ray_t corner_ray = camera_get_ray(&cam, 1.0, 1.0);
    check("top-right ray goes right", corner_ray.direction.e[0] > 0.0);
    check("top-right ray goes up",    corner_ray.direction.e[1] > 0.0);

    /* Ray through bottom-left (u=0, v=0) should have negative x and y */
    ray_t bl_ray = camera_get_ray(&cam, 0.0, 0.0);
    check("bottom-left ray goes left", bl_ray.direction.e[0] < 0.0);
    check("bottom-left ray goes down", bl_ray.direction.e[1] < 0.0);

    /* Camera with aperture: ray origin should be offset from camera center */
    camera_t cam_dof = camera_create(
        vec3(0.0, 0.0, 0.0),
        vec3(0.0, 0.0, -1.0),
        vec3(0.0, 1.0, 0.0),
        90.0, 1.0,
        2.0, /* large aperture */
        1.0
    );
    check_double("dof lens radius = 1.0", cam_dof.lens_radius, 1.0);

    printf("\n%d/%d tests passed\n", passed, passed + failed);
    return failed == 0 ? 0 : 1;
}
