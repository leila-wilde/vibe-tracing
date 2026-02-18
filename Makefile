CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O3 -fopenmp
SRCDIR = src
TESTDIR = tests
OUTDIR = output

# Source files
COMMON_OBJS = $(SRCDIR)/vec3.o $(SRCDIR)/ray.o $(SRCDIR)/hittable.o $(SRCDIR)/sphere.o \
              $(SRCDIR)/camera.o $(SRCDIR)/material.o
MAIN_OBJS = $(COMMON_OBJS) $(SRCDIR)/main.o

TEST_BINS = test_vec3 test_ray test_sphere test_material test_camera

.PHONY: all clean test run

all: vibe_tracing

# Main program target
vibe_tracing: $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# Run the main program
run: vibe_tracing
	./vibe_tracing

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Unit tests
test: $(TEST_BINS)
	@echo "\n--- Running all tests ---"
	@./test_vec3
	@./test_ray
	@./test_sphere
	@./test_material
	@./test_camera

test_vec3: $(COMMON_OBJS) $(TESTDIR)/test_vec3.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

test_ray: $(COMMON_OBJS) $(TESTDIR)/test_ray.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

test_sphere: $(COMMON_OBJS) $(TESTDIR)/test_sphere.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

test_material: $(COMMON_OBJS) $(TESTDIR)/test_material.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

test_camera: $(COMMON_OBJS) $(TESTDIR)/test_camera.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/*.o $(TESTDIR)/*.o vibe_tracing $(TEST_BINS)
	rm -f $(OUTDIR)/*.ppm $(OUTDIR)/*.png
