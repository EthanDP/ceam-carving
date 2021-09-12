#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"

Kernel create_blur_kernel(int strength, int size);

void blur (struct Image *image, int strength, int size) {
    /*
    *   Gaussian blur
    */

    Kernel blur_kernel = create_blur_kernel(strength, size);

    // This image copy will be used to get original pixel values
    // and will not be modified.
    struct Image temp;
    copy_image(&temp, *image);

    double *new_pixel;
    new_pixel = malloc(image->pixel_width * sizeof(double));

    unsigned char new_byte;

    // Stores the position of a kernel point relative to the image
    int current_y;
    int current_x;

    log_message("Bluring image...\n");

    // These first two loops iterate over evey pixel in the original image
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {

            for (int pixel_idx = 0; pixel_idx < sizeof(new_pixel); pixel_idx++) {
                new_pixel[pixel_idx] = 0.0;
            }

            // These two loops iterate over each position in the kernel
            for (int kernel_y = 0; kernel_y < blur_kernel.kernel_size; kernel_y++) {
                for (int kernel_x = 0; kernel_x < blur_kernel.kernel_size; kernel_x++) {

                    current_y = y - (kernel_y - 1);
                    current_x = x - (kernel_x - 1);

                    // This loop iterates over each byte in the pixel being modified
                    for (int k = 0; k < image->pixel_width; k++) {
                        if (current_y >= 0 && current_y < image->height && current_x >= 0 && current_x < image->width) {
                            // This line is horrible but it multiplies a pixel byte value by the corresponding
                            // kernel value and adds it to the pixel value
                            new_pixel[k] += temp.pixel_array[current_y][current_x][k] * blur_kernel.kernel_array[kernel_y][kernel_x];
                        } else {
                            new_pixel[k] += temp.pixel_array[y][x][k] * blur_kernel.kernel_array[kernel_y][kernel_x];
                        }
                    }
                }
            }

            for (int byte_idx = 0; byte_idx < image->pixel_width; byte_idx++) {
                new_byte = (byte) new_pixel[byte_idx];
                image->pixel_array[y][x][byte_idx] = new_byte;
            }
        }
    }

    free_image(&temp);
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
