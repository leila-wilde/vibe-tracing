# Project Specification: Vibe Tracing (C Language)

## 1. Project overview

Vibe Tracing is a high-performance path tracer written in pure C. This project implements a modular ray tracing engine using clean C structures and functional patterns to generate photorealistic 3D images with global illumination, reflections, and refractions.

## 2. Technical stack

- **Language:** C (C11 standard)

- **Output format:** PPM (Portable Pixmap)

- **Math library:** Custom `vec3` utility.

- **Build system:** Makefile (GCC).

## 3. Core architecture

### 3.1 Data structures

`vec3`: A structure containing `double e[3]`. Used for points, colors, and vectors.

`ray`: Contains an origin point3 and a direction vec3.

`hit_record`: Stores intersection data (`p`, `normal`, `t`, `front_face`, and a `material` pointer).

`hittable`: A generic interface for objects using a function pointer for the hit logic.

`material`: A structure with a function pointer for `scatter` behavior.

### 3.2 Modular components

1. **Vector Math**: core linear algebra (dot, cross, unit vectors, random generation).

2. **Ray engine**: recursive color calculation and ray-object interaction.

3. **Camera**: handles FOV, orientation (look-at), and defocus blur.

4. **Materials**: Lambertian (matte), Metal (shiny), and Dielectric (glass).

## 4. Feature requirements

- [ ] **PPM image generation:** valid header and pixel stream.
- [ ] **Antialiasing:** Multi-sampling (MSAA) per pixel.
- [ ] **Geometry:** Sphere primitive with normal calculations.
- [ ] **Global Illumination:** Diffuse scattering with recursion depth limits.
- [ ] **Optics:** reflection and Snell’s Law refraction.
- [ ] **Camera control:** position, target, and depth-of-field.

## 5. Implementation roadmap (prompting sequence)

### Step 1: foundation & math

**Prompt:** "Create a C11 header vec3.h and implementation vec3.c for 3D vector math. Include basic operations (add, sub, mul, div, dot, cross, length) and utilities for random double generation and random unit vectors. Ensure all functions are efficient."

### Step 2: image output & basic ray

**Prompt:** "Create a ray.h struct and a main.c that outputs a 256x256 PPM image. The image should visualize a simple gradient background calculated by the ray direction ($y$-component lerp). Include a basic Makefile to compile."

### Step 3: geometry & intersections

**Prompt:** "Implement a hittable.h interface using a struct with a function pointer for hit. Create a sphere.h and sphere.c that implements this interface. Update main.c to render a single sphere in the center of the screen."

### Step 4: antialiasing & camera

**Prompt:** "Create a camera.h module. Move camera logic from main into this module. Implement multi-sampling (MSAA) by shooting multiple random rays per pixel and averaging the color."

### Step 5: materials (the scatter system)

**Prompt:** "Define a material struct with a scatter function pointer. Implement three types: Lambertian (diffuse), Metal (reflective with fuzziness), and Dielectric (glass using Schlick's approximation). Update the hit_record to include a pointer to the material hit."

### Step 6: the final scene

**Prompt:** "Update the main render loop to handle recursive ray bounces (depth limit of 50). Create a function to generate a complex scene with many spheres of different materials. Optimize for a 1200x800 final render."

## 6. Documentation & logging

### 6.1 COPILOT.md

This file serves as the instruction manual for the coding agent regarding style, workflow, constrainsts etc. 

### 6.2 SESSION.md

This file is the Official Log of the development session. Every interaction must be recorded in the following format:

```
[timestamp] - [feature/task]
[The exact prompt sent to the model]
[Model Name (e.g., GPT-4o, Claude 3.5 Sonnet, etc.)]
```

## 7. Development guidelines

- **Encapsulation:** use static functions for internal logic within .c files.

- **Memory management:** use a central hittable_list to manage objects; ensure a cleanup function is called at the end of main.

- **Randomness:** implement a consistent random_double() wrapper around rand().

- **Performance:** use const pointers for large structs and inline for math utilities.

## 8. Project structure

``` 
vibe-tracing/
├── src/
│   ├── main.c          # Entry point and render loop
│   ├── vec3.h/c        # Math utilities
│   ├── ray.h           # Ray definition
│   ├── camera.h/c      # Viewport and camera logic
│   ├── material.h/c    # Scatter logic
│   ├── hittable.h      # Abstract object interface
│   ├── sphere.h/c      # Sphere implementation
│   └── utils.h         # Constants and random helpers
├── output/             # Rendered images (.ppm)
├── Makefile            # Build system
├── COPILOT.md          # Instructions for the agent
└── SESSION.md          # Prompt history and session log
```
