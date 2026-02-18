#include "../src/ray.h"
#include "../src/vec3.h"
#include <stdio.h>
#include <math.h>

#define EPSILON 1e-9

static int passed = 0, failed = 0;

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
    vec3_t origin = vec3(1.0, 2.0, 3.0);
    vec3_t direction = vec3(4.0, 5.0, 6.0);
    ray_t r = ray(origin, direction);

    /* ray() stores origin and direction */
    check_vec3("ray origin",    r.origin,    origin);
    check_vec3("ray direction", r.direction, direction);

    /* ray_at(t=0) == origin */
    check_vec3("ray_at t=0", ray_at(r, 0.0), origin);

    /* ray_at(t=1) == origin + direction */
    check_vec3("ray_at t=1", ray_at(r, 1.0), vec3(5.0, 7.0, 9.0));

    /* ray_at(t=0.5) == origin + 0.5*direction */
    check_vec3("ray_at t=0.5", ray_at(r, 0.5), vec3(3.0, 4.5, 6.0));

    /* ray_at with negative t goes behind origin */
    check_vec3("ray_at t=-1", ray_at(r, -1.0), vec3(-3.0, -3.0, -3.0));

    printf("\n%d/%d tests passed\n", passed, passed + failed);
    return failed == 0 ? 0 : 1;
}
