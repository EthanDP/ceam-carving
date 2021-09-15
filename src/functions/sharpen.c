#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"
#include "functions.h"

Kernel create_sharpen_kernel(int strength, int size);

void sharpen (struct Image *image, int strength, int size) {
    Kernel sharpen_kernel = create_sharpen_kernel(strength, size);
    log_message("Sharpening image...\n");
    apply_kernel(image, sharpen_kernel, SHARPEN);
}

Kernel create_sharpen_kernel(int strength, int size) {
    log_message("Generating sharpen kernel...\n");

    Kernel sharpen_kernel;

    if (size % 2 == 0) {
        sharpen_kernel.size = size - 1;
    } else {
        sharpen_kernel.size = size;
    }

    double outer_points = sharpen_kernel.size * sharpen_kernel.size - 1;

    double center_value = 1.0 + (strength / 10.0);
    double outer_value = -1.0 * (center_value - 1)/outer_points;

    int center = sharpen_kernel.size / 2;

    sharpen_kernel.kernel_array = malloc(sharpen_kernel.size * sizeof(*sharpen_kernel.kernel_array));
    for (int y = 0; y < sharpen_kernel.size; y++) {
        sharpen_kernel.kernel_array[y] = malloc(sharpen_kernel.size * sizeof(double));
        for (int x = 0; x < sharpen_kernel.size; x++) {
            if (y == center && x == center) {
                sharpen_kernel.kernel_array[y][x] = center_value;
            } else {
                sharpen_kernel.kernel_array[y][x] = outer_value;
            }
        }
    }

    return sharpen_kernel;
}