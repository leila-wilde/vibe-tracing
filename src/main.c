#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* Image dimensions */
#define IMAGE_WIDTH 1200
#define IMAGE_HEIGHT 800
#define SAMPLES_PER_PIXEL 500
#define MAX_DEPTH 50
#define USE_OPENMP 0

/* Construct a ray from origin and direction */
ray_t ray(const vec3_t origin, const vec3_t direction) {
    return (ray_t){origin, direction};
}

/* Get point at parameter t along the ray */
vec3_t ray_at(const ray_t r, double t) {
    return vec3_add(r.origin, vec3_mul(r.direction, t));
}

/* Calculate color based on ray-scene intersection with recursion */
static vec3_t ray_color(const ray_t r, const hittable_list_t *world, int depth) {
    hit_record_t rec = {0};

    if (depth <= 0) {
        return vec3(0.0, 0.0, 0.0);
    }

    if (hittable_list_hit(world, r, 0.001, INFINITY, &rec)) {
        ray_t scattered = {0};
        vec3_t attenuation = {0};

        if (rec.material && rec.material->scatter) {
            if (rec.material->scatter(rec.material->data, r, &rec, &attenuation,
                                      &scattered)) {
                vec3_t color = ray_color(scattered, world, depth - 1);
                return vec3(attenuation.e[0] * color.e[0],
                           attenuation.e[1] * color.e[1],
                           attenuation.e[2] * color.e[2]);
            }
        }
        return vec3(0.0, 0.0, 0.0);
    }

    vec3_t unit_direction = vec3_normalize(r.direction);
    double t = 0.5 * (unit_direction.e[1] + 1.0);
    vec3_t white = vec3(1.0, 1.0, 1.0);
    vec3_t blue = vec3(0.5, 0.7, 1.0);
    return vec3_add(vec3_mul(white, 1.0 - t), vec3_mul(blue, t));
}

/* Write color value to PPM file (0-255) with gamma correction */
static void write_color(FILE *out, const vec3_t color, int samples) {
    double r = color.e[0] / samples;
    double g = color.e[1] / samples;
    double b = color.e[2] / samples;

    /* Gamma correction (gamma = 2.0) */
    r = sqrt(r);
    g = sqrt(g);
    b = sqrt(b);

    int ir = (int)(255.999 * clamp(r, 0.0, 1.0));
    int ig = (int)(255.999 * clamp(g, 0.0, 1.0));
    int ib = (int)(255.999 * clamp(b, 0.0, 1.0));
    fprintf(out, "%d %d %d\n", ir, ig, ib);
}

int main(void) {
    /* Create output directory if needed */
    (void)system("mkdir -p output");

    /* Create world (scene) */
    hittable_list_t *world = hittable_list_create();
    if (!world) {
        fprintf(stderr, "Error: could not create hittable list\n");
        return 1;
    }

    /* Create materials */
    material_t mat_ground = lambertian_create(vec3(0.5, 0.5, 0.5));

    /* Create spheres with materials */
    sphere_t *ground = sphere_create(vec3(0.0, -1000.0, 0.0), 1000.0, &mat_ground);
    if (ground) {
        hittable_list_add(world, sphere_to_hittable(ground));
    }

    /* Persistent material storage for random spheres (max 22x22 = 484) */
    material_t *random_mats = malloc(484 * sizeof(material_t));
    if (!random_mats) {
        fprintf(stderr, "Error: could not allocate random materials\n");
        hittable_list_destroy(world);
        return 1;
    }
    int num_random_mats = 0;

    /* Generate random scene with many spheres */
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            vec3_t center = vec3(a + 0.9 * random_double(), 0.2,
                                b + 0.9 * random_double());

            if (vec3_length(vec3_sub(center, vec3(4.0, 0.2, 0.0))) > 0.9) {
                sphere_t *sphere = NULL;
                material_t mat = {0};

                if (choose_mat < 0.8) {
                    /* Diffuse sphere */
                    vec3_t albedo = vec3(random_double() * random_double(),
                                        random_double() * random_double(),
                                        random_double() * random_double());
                    mat = lambertian_create(albedo);
                } else if (choose_mat < 0.95) {
                    /* Metal sphere */
                    vec3_t albedo = vec3(0.5 * (1.0 + random_double()),
                                        0.5 * (1.0 + random_double()),
                                        0.5 * (1.0 + random_double()));
                    double fuzz = 0.5 * random_double();
                    mat = metal_create(albedo, fuzz);
                } else {
                    /* Glass sphere */
                    mat = dielectric_create(1.5);
                }

                /* Store material in persistent array so pointer remains valid */
                random_mats[num_random_mats] = mat;
                sphere = sphere_create(center, 0.2, &random_mats[num_random_mats]);
                num_random_mats++;

                if (sphere) {
                    hittable_list_add(world, sphere_to_hittable(sphere));
                }
            }
        }
    }

    /* Three main spheres */
    material_t mat_center = lambertian_create(vec3(0.4, 0.2, 0.1));
    sphere_t *center = sphere_create(vec3(-4.0, 1.0, 0.0), 1.0, &mat_center);
    if (center) {
        hittable_list_add(world, sphere_to_hittable(center));
    }

    material_t mat_middle = dielectric_create(1.5);
    sphere_t *middle = sphere_create(vec3(0.0, 1.0, 0.0), 1.0, &mat_middle);
    if (middle) {
        hittable_list_add(world, sphere_to_hittable(middle));
    }

    material_t mat_right = metal_create(vec3(0.7, 0.6, 0.5), 0.0);
    sphere_t *right = sphere_create(vec3(4.0, 1.0, 0.0), 1.0, &mat_right);
    if (right) {
        hittable_list_add(world, sphere_to_hittable(right));
    }

    /* Camera setup */
    camera_t camera = camera_create(
        vec3(13.0, 2.0, 3.0),          /* lookfrom */
        vec3(0.0, 0.0, 0.0),           /* lookat */
        vec3(0.0, 1.0, 0.0),           /* vup */
        20.0,                           /* vfov (degrees) */
        (double)IMAGE_WIDTH / IMAGE_HEIGHT, /* aspect ratio */
        0.1,                            /* aperture (depth of field) */
        10.0                            /* focus distance */
    );

    /* Open output file */
    FILE *out = fopen("output/final.ppm", "w");
    if (!out) {
        fprintf(stderr, "Error: could not open output/final.ppm\n");
        hittable_list_destroy(world);
        return 1;
    }

    /* Write PPM header */
    fprintf(out, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    fflush(out);

    /* Pre-allocate buffer for all pixels to avoid file synchronization issues */
    vec3_t *pixel_buffer = malloc(IMAGE_WIDTH * IMAGE_HEIGHT * sizeof(vec3_t));
    if (!pixel_buffer) {
        fprintf(stderr, "Error: could not allocate pixel buffer\n");
        fclose(out);
        hittable_list_destroy(world);
        return 1;
    }

    /* Render each pixel with multisampling (parallelized) */
    fprintf(stderr, "Rendering...\n");
    #if USE_OPENMP
    #pragma omp parallel for schedule(dynamic, 100)
    #endif
    for (int pixel_idx = 0; pixel_idx < IMAGE_WIDTH * IMAGE_HEIGHT; pixel_idx++) {
        int j = IMAGE_HEIGHT - 1 - (pixel_idx / IMAGE_WIDTH);
        int i = pixel_idx % IMAGE_WIDTH;
        
        vec3_t pixel_color = vec3(0.0, 0.0, 0.0);

        /* Multiple samples per pixel for antialiasing */
        for (int s = 0; s < SAMPLES_PER_PIXEL; s++) {
            double u = (i + random_double()) / (IMAGE_WIDTH - 1);
            double v = (j + random_double()) / (IMAGE_HEIGHT - 1);
            ray_t r = camera_get_ray(&camera, u, v);
            pixel_color = vec3_add(pixel_color, ray_color(r, world, MAX_DEPTH));
        }

        /* Store in buffer */
        pixel_buffer[pixel_idx] = pixel_color;
    }
    fprintf(stderr, "Rendering complete. Writing file...\n");
    fflush(stderr);

    /* Write pixel buffer to file */
    for (int idx = 0; idx < IMAGE_WIDTH * IMAGE_HEIGHT; idx++) {
        write_color(out, pixel_buffer[idx], SAMPLES_PER_PIXEL);
    }
    fflush(out);

    fprintf(stderr, "\nDone.\n");
    fclose(out);
    free(pixel_buffer);
    hittable_list_destroy(world);

    /* Clean up materials */
    if (mat_ground.destroy) mat_ground.destroy(mat_ground.data);
    if (mat_center.destroy) mat_center.destroy(mat_center.data);
    if (mat_middle.destroy) mat_middle.destroy(mat_middle.data);
    if (mat_right.destroy) mat_right.destroy(mat_right.data);
    for (int i = 0; i < num_random_mats; i++) {
        if (random_mats[i].destroy) random_mats[i].destroy(random_mats[i].data);
    }
    free(random_mats);

    return 0;
}
