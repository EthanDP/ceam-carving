#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"
#include "functions.h"

Kernel create_mushroomify_kernel(int strength);

void mushroomify (struct Image *image, int strength) {
    Kernel mushroomify_kernel = create_mushroomify_kernel(strength);
    log_message("Bluring image...\n");

    apply_kernel(image, mushroomify_kernel, BLUR);
}

Kernel create_mushroomify_kernel(int strength) {
    log_message("Generating sharpen kernel...\n");

    Kernel mushroomify_kernel;

    mushroomify_kernel.size = 20;

    double outer_points = mushroomify_kernel.size * mushroomify_kernel.size - 1;

    double center_value = 1.0 + (strength / 10.0);
    double outer_value = -1.0 * (center_value - 1)/outer_points;

    int center = mushroomify_kernel.size / 2;

    mushroomify_kernel.kernel_array = malloc(mushroomify_kernel.size * sizeof(*mushroomify_kernel.kernel_array));
    for (int y = 0; y < mushroomify_kernel.size; y++) {
        mushroomify_kernel.kernel_array[y] = malloc(mushroomify_kernel.size * sizeof(double));
        for (int x = 0; x < mushroomify_kernel.size; x++) {
            if (y == center && x == center) {
                mushroomify_kernel.kernel_array[y][x] = center_value;
            } else {
                mushroomify_kernel.kernel_array[y][x] = outer_value;
            }
        }
    }

    return mushroomify_kernel;
}