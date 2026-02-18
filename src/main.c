#include "vec3.h"
#include "ray.h"
#include <stdio.h>
#include <stdlib.h>

/* Image dimensions */
#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256

/* Construct a ray from origin and direction */
ray_t ray(const vec3_t origin, const vec3_t direction) {
    return (ray_t){origin, direction};
}

/* Get point at parameter t along the ray */
vec3_t ray_at(const ray_t r, double t) {
    return vec3_add(r.origin, vec3_mul(r.direction, t));
}

/* Calculate color based on ray direction (simple gradient) */
static vec3_t ray_color(const ray_t r) {
    vec3_t unit_direction = vec3_normalize(r.direction);
    double t = 0.5 * (unit_direction.e[1] + 1.0);
    vec3_t white = vec3(1.0, 1.0, 1.0);
    vec3_t blue = vec3(0.5, 0.7, 1.0);
    vec3_t blended = vec3_add(vec3_mul(white, 1.0 - t), vec3_mul(blue, t));
    return blended;
}

/* Write color value to PPM file (0-255) */
static void write_color(FILE *out, const vec3_t color) {
    int r = (int)(255.999 * color.e[0]);
    int g = (int)(255.999 * color.e[1]);
    int b = (int)(255.999 * color.e[2]);
    fprintf(out, "%d %d %d\n", r, g, b);
}

int main(void) {
    /* Create output directory if needed */
    (void)system("mkdir -p output");

    /* Open output file */
    FILE *out = fopen("output/gradient.ppm", "w");
    if (!out) {
        fprintf(stderr, "Error: could not open output/gradient.ppm\n");
        return 1;
    }

    /* Write PPM header */
    fprintf(out, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    /* Camera setup */
    vec3_t origin = vec3(0.0, 0.0, 0.0);
    vec3_t horizontal = vec3(4.0, 0.0, 0.0);
    vec3_t vertical = vec3(0.0, 4.0, 0.0);
    vec3_t lower_left = vec3_sub(vec3_sub(origin, vec3_mul(horizontal, 0.5)),
                                  vec3_mul(vertical, 0.5));
    lower_left = vec3_sub(lower_left, vec3(0.0, 0.0, 1.0));

    /* Render each pixel */
    for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
        fprintf(stderr, "\rScanlines remaining: %d  ", j);
        fflush(stderr);

        for (int i = 0; i < IMAGE_WIDTH; i++) {
            double u = (double)i / (IMAGE_WIDTH - 1);
            double v = (double)j / (IMAGE_HEIGHT - 1);

            vec3_t pixel = vec3_add(lower_left,
                                    vec3_add(vec3_mul(horizontal, u),
                                            vec3_mul(vertical, v)));
            vec3_t direction = vec3_sub(pixel, origin);
            ray_t r = ray(origin, direction);
            vec3_t color = ray_color(r);

            write_color(out, color);
        }
    }

    fprintf(stderr, "\nDone.\n");
    fclose(out);
    return 0;
}
