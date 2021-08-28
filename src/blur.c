#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "kernel.h"

Kernel create_blur_kernel();

void blur (struct Image *image) {
    /*
    *   Gaussian blur
    */

    Kernel blur_kernel = create_blur_kernel();

    struct Image temp;

    copy_image(&temp, *image);

    printf("Here's the new width: %i", temp.width);

    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {
            for (int k = 0; k < image->pixel_width; k++) {
                //TODO: logic for applying a kernel to image :(
            }
        }
    }

    free_image(&temp);
}

Kernel create_blur_kernel() {
    /*
    *   Gaussian blur
    */

    Kernel gaussian_kernel;
    gaussian_kernel.kernel_size = 3;
    gaussian_kernel.kernel_array = malloc(gaussian_kernel.kernel_size * sizeof(*gaussian_kernel.kernel_array));
    for (int i = 0; i < 3; i++) {
        gaussian_kernel.kernel_array[i] = malloc(sizeof(double));
        for (int j = 0; j < gaussian_kernel.kernel_size; j++) {
            gaussian_kernel.kernel_array[i][j] = .1;
        }
    }

    return gaussian_kernel;
}