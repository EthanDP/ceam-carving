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

    // This image copy will be used to get original pixel values
    // and will not be modified.
    struct Image temp;
    copy_image(&temp, *image);

    // These first two loops iterate over evey pixel in the original image
    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {

            // This loop resets the pixel byte array
            for (int pixel_idx = 0; pixel_idx < image->pixel_width; pixel_idx++) {
                image->pixel_array[i][j][pixel_idx] = 0;
            }

            // These two loops iterate over each position in the kernel
            for (int i2 = 0; i2 < blur_kernel.kernel_size; i2++) {
                for (int j2 = 0; j2 < blur_kernel.kernel_size; j2++) {

                    // This loop iterates over each byte in the pixel being modified
                    for (int k = 0; k < image->pixel_width; k++) {
                        if (i - (i2 - 1) >= 0 && i - (i2 - 1) < image->width && j - (j2 - 1) >= 0 && j - (j2 - 1) < image->height) {
                            // This line is horrible but it multiplies a pixel byte value by the corresponding
                            // kernel value and adds it to the pixel value
                            //printf("Current pixel value: %i\n", temp.pixel_array[i - (i2 - 1)][j - (j2 - 1)][k]);
                            image->pixel_array[i][j][k] += (unsigned char)(temp.pixel_array[i - (i2 - 1)][j - (j2 - 1)][k] * blur_kernel.kernel_array[i2][j2]);
                        }
                    }
                }
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