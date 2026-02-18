CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O3 -fopenmp
SRCDIR = src
TESTDIR = tests
OUTDIR = output

# Source files
COMMON_OBJS = $(SRCDIR)/vec3.o $(SRCDIR)/hittable.o $(SRCDIR)/sphere.o \
              $(SRCDIR)/camera.o $(SRCDIR)/material.o
MAIN_OBJS = $(COMMON_OBJS) $(SRCDIR)/main.o

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
test: test_vec3

test_vec3: $(COMMON_OBJS) $(TESTDIR)/test_vec3.o
	$(CC) $(CFLAGS) -o $@ $^ -lm
	./test_vec3

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/*.o $(TESTDIR)/*.o vibe_tracing test_vec3
	rm -f $(OUTDIR)/*.ppm
