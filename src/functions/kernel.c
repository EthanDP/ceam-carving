#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"
#include "functions.h"

void apply_kernel(struct Image *image, Kernel kernel, int mode) {
    // This image copy will be used to get original pixel values
    // and will not be modified.
    struct Image temp;
    copy_image(&temp, *image);

    double *new_pixel;
    new_pixel = malloc(image->pixel_width * sizeof(double));

    byte new_byte;

    // Stores the position of a kernel point relative to the image
    int current_y;
    int current_x;

    log_message("Applying kernel to image...\n");

    // These first two loops iterate over evey pixel in the original image
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {

            for (int pixel_idx = 0; pixel_idx < sizeof(new_pixel); pixel_idx++) {
                new_pixel[pixel_idx] = 0.0;
            }

            // These two loops iterate over each position in the kernel
            for (int kernel_y = 0; kernel_y < kernel.kernel_size; kernel_y++) {
                for (int kernel_x = 0; kernel_x < kernel.kernel_size; kernel_x++) {

                    current_y = y - (kernel_y - 1);
                    current_x = x - (kernel_x - 1);

                    // This loop iterates over each byte in the pixel being modified
                    for (int k = 0; k < image->pixel_width; k++) {
                        if (current_y >= 0 && current_y < image->height && current_x >= 0 && current_x < image->width) {
                            // This line is horrible but it multiplies a pixel byte value by the corresponding
                            // kernel value and adds it to the pixel value
                            new_pixel[k] += temp.pixel_array[current_y][current_x][k] * kernel.kernel_array[kernel_y][kernel_x];
                        } else {
                            new_pixel[k] += temp.pixel_array[y][x][k] * kernel.kernel_array[kernel_y][kernel_x];
                        }
                    }
                }
            }

            for (int byte_idx = 0; byte_idx < image->pixel_width; byte_idx++) {
                int int_byte = (int) new_pixel[byte_idx];
                if (mode == BLUR || mode == MUSHROOMIFY) {
                    new_byte = (byte) int_byte;
                } else if (mode == SHARPEN) {
                    if (int_byte > 255) {
                        new_byte = 255;
                    } else if (int_byte < 0) {
                        new_byte = 0;
                    } else {
                        new_byte = (byte) int_byte;
                    }
                }

                image->pixel_array[y][x][byte_idx] = new_byte;
            }
        }
    }

    free_image(&temp);
}
