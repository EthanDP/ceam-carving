#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"

Kernel create_blur_kernel();

void blur (struct Image *image, int strength) {
    /*
    *   Gaussian blur
    */

    log_message("Bluring image...\n");

    Kernel blur_kernel = create_blur_kernel(strength);

    // This image copy will be used to get original pixel values
    // and will not be modified.
    struct Image temp;
    copy_image(&temp, *image);

    double *new_pixel;
    new_pixel = malloc(image->pixel_width * sizeof(double));

    unsigned char new_byte;

    printf("Corresponding width and heigh stuff\n");

    // These first two loops iterate over evey pixel in the original image
    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {

            for (int pixel_idx = 0; pixel_idx < sizeof(new_pixel); pixel_idx++) {
                new_pixel[pixel_idx] = 0.0;
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
                            new_pixel[k] += temp.pixel_array[i - (i2 - 1)][j - (j2 - 1)][k] * blur_kernel.kernel_array[i2][j2];
                        } else {
                            new_pixel[k] += temp.pixel_array[i][j][k] * blur_kernel.kernel_array[i2][j2];
                        }

                        //printf("New value: %f\n", blur_kernel.kernel_array[i2][j2]);
                    }
                }
            }

            for (int pixel_byte = 0; pixel_byte < image->pixel_width; pixel_byte++) {
                new_byte = (unsigned char) new_pixel[pixel_byte];
                printf("New byte: %x\n", new_byte);
                image->pixel_array[i][j][pixel_byte] = new_byte;
                //printf("Old value byte: %i and new value %i \n", temp.pixel_array[i][j][pixel_byte], image->pixel_array[i][j][pixel_byte]);
            }
        }
    }

    free_image(&temp);
}

Kernel create_blur_kernel(int strength) {
    /*
    *   Gaussian blur
    */

    log_message("Generating blur kernel...\n");

    double center_value = 1.0 - (double)strength / 100;
    double outer_value = 1.0 * (1.0 - center_value)/8.0;

    Kernel gaussian_kernel;
    gaussian_kernel.kernel_size = 3;
    gaussian_kernel.kernel_array = malloc(gaussian_kernel.kernel_size * sizeof(*gaussian_kernel.kernel_array));
    for (int i = 0; i < gaussian_kernel.kernel_size; i++) {
        gaussian_kernel.kernel_array[i] = malloc(sizeof(double));
        for (int j = 0; j < gaussian_kernel.kernel_size; j++) {
            if (i == 1 && j == 1) {
                gaussian_kernel.kernel_array[i][j] = center_value;
            } else {
                gaussian_kernel.kernel_array[i][j] = outer_value;
            }
        }
    }

    return gaussian_kernel;
}
