#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"

Kernel create_sharpen_kernel(int strength, int size);

void sharpen (struct Image *image, int strength, int size) {
    Kernel sharpen_kernel = create_sharpen_kernel(strength, size);
    log_message("Sharpening image...\n");
    apply_kernel(image, sharpen_kernel);
}

Kernel create_sharpen_kernel(int strength, int size) {
    log_message("Generating sharpen kernel...\n");

    Kernel sharpen_kernel;

    if (size % 2 == 0) {
        sharpen_kernel.kernel_size = size - 1;
    } else {
        sharpen_kernel.kernel_size = size;
    }

    double outer_points = sharpen_kernel.kernel_size * sharpen_kernel.kernel_size - 1;

    double center_value = strength;
    double outer_value = -1.0 * (center_value - 1)/outer_points;

    int center = sharpen_kernel.kernel_size / 2;

    sharpen_kernel.kernel_array = malloc(sharpen_kernel.kernel_size * sizeof(*sharpen_kernel.kernel_array));
    for (int y = 0; y < sharpen_kernel.kernel_size; y++) {
        sharpen_kernel.kernel_array[y] = malloc(sharpen_kernel.kernel_size * sizeof(double));
        for (int x = 0; x < sharpen_kernel.kernel_size; x++) {
            if (y == center && x == center) {
                sharpen_kernel.kernel_array[y][x] = center_value;
            } else {
                sharpen_kernel.kernel_array[y][x] = outer_value;
            }
        }
    }

    return sharpen_kernel;
}