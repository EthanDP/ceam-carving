#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"
#include "functions.h"

Kernel create_blur_kernel(int strength, int size);

void blur (struct Image *image, int strength, int size) {
    /*
    *   Gaussian blur
    */

    Kernel blur_kernel = create_blur_kernel(strength, size);
    log_message("Bluring image...\n");

    apply_kernel(image, blur_kernel, BLUR);
}

Kernel create_blur_kernel(int strength, int size) {
    /*
    *   Gaussian blur
    */

    log_message("Generating blur kernel...\n");

    Kernel blur_kernel;

    if (size % 2 == 0) {
        blur_kernel.kernel_size = size - 1;
    } else {
        blur_kernel.kernel_size = size;
    }

    double outer_points = blur_kernel.kernel_size * blur_kernel.kernel_size - 1;

    double center_value = 1.0 - (double)strength / 100;
    double outer_value = 1.0 * (1.0 - center_value)/outer_points;

    int center = blur_kernel.kernel_size / 2;

    blur_kernel.kernel_array = malloc(blur_kernel.kernel_size * sizeof(*blur_kernel.kernel_array));
    for (int y = 0; y < blur_kernel.kernel_size; y++) {
        blur_kernel.kernel_array[y] = malloc(blur_kernel.kernel_size * sizeof(double));
        for (int x = 0; x < blur_kernel.kernel_size; x++) {
            if (y == center && x == center) {
                blur_kernel.kernel_array[y][x] = center_value;
            } else {
                blur_kernel.kernel_array[y][x] = outer_value;
            }
        }
    }

    return blur_kernel;
}
