#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"
#include "functions.h"

void populate_kernels();

void detect_edges(struct Image *image) {
    Kernel vertical_kernel;
    Kernel horizontal_kernel;

    populate_kernels(&vertical_kernel, &horizontal_kernel);

    struct Image copy;
    copy_image(&copy, image);

    log_message("Detecting edges...\n");

    apply_kernel(&copy, horizontal_kernel, EDGE_DETECT);
    // TODO: Fix weird memory issues
    apply_kernel(image, vertical_kernel, EDGE_DETECT);
    sum_images(image, &copy);
}

void populate_kernels(Kernel *vertical, Kernel *horizontal) {
    
    log_message("Populating kernels...\n");

    vertical->size = 3;
    horizontal->size = 3;

    double vertical_array[3][3] = {
        {-.25, 0.0, .25},
        {-.5, 0.0, .5},
        {-.25, 0.0, .25}
    };

    double horizontal_array[3][3] = {
        {-.25, -.5, -.25},
        {0.0, 0.0, 0.0},
        {.25, .5, .25}
    };

    vertical->kernel_array = malloc(vertical->size * sizeof(*vertical->kernel_array));
    horizontal->kernel_array = malloc(horizontal->size * sizeof(*horizontal->kernel_array));

    for (int y = 0; y < vertical->size; y++) {
        vertical->kernel_array[y] = malloc(vertical->size * sizeof(*vertical->kernel_array[y]));
        horizontal->kernel_array[y] = malloc(horizontal->size * sizeof(*horizontal->kernel_array[y]));
        for (int x = 0; x < vertical->size; x++) {
            vertical->kernel_array[y][x] = vertical_array[y][x];
            horizontal->kernel_array[y][x] = horizontal_array[y][x];
        }
    }
}
