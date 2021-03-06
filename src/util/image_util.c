#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "image_util.h"
#include "byte_util.h"
#include "logging_util.h"
#include "bmp.h"

struct Image open_image(char filename[], int size) {
    /*
    * Reads a data from an image file and stores it in
    * an image struct.
    *
    * filename: a string representing the input filename
    * size: the length of the filename
    */

    struct Image image;
    FILE *file;
    if (file = fopen(filename, "rb")) {
        image.image_file = file;
        image.error_code = NO_ERROR;
    } else {
        image.error_code = INVALID_FILENAME;
        return image;
    }
    
    char extension[4] = {BLANK, BLANK, BLANK, BLANK};

    int curr_index = 3;
    for (int i = size-1; i > 0; i--) {
        if (curr_index < 0) {
            log_error("Invalid Extension");
            break;
        } else if ((int)filename[i] == (int)'.') {
            break;
        } else if ((int)filename[i] != 0) {
            extension[curr_index] = filename[i];
            curr_index -= 1;
        }
    }

    if (strcmp(extension, "@bmp") == 0) {
        read_bmp(&image);
    } else {
        log_error("Invalid file type.");
    }

    return image;
}

void write_image(struct Image *image, char filetype[]) {
    // TODO: Check for different filetypes and call specific function accordingly
    if (strcmp(filetype, "bmp") == 0) {
        write_bmp(image);
    } 

    free_image(image);
    // TODO: Add output checking to main.c so invalid output filetypes can't be used
}

struct Image copy_image(struct Image *original) {
    struct Image copy;
    copy.width = original->width;
    copy.height = original->height;
    copy.pixel_width = original->pixel_width;

    copy.pixel_array = malloc(copy.height * sizeof(*copy.pixel_array));
    printf("Does it get past the initial malloc?\n");
    for (int y = 0; y < copy.height; y++) {
        copy.pixel_array[y] = malloc(copy.width * sizeof(*copy.pixel_array[y]));
        printf("Does it even do this?\n");

        for (int x = 0; x < copy.width; x++) {
            copy.pixel_array[y][x] = malloc(copy.pixel_width * sizeof(*copy.pixel_array[y][x]));

            for (int k = 0; k < copy.pixel_width; k++) {
                copy.pixel_array[y][x][k] = original->pixel_array[y][x][k];
            }
        }
        printf("How many times\n");
    }
}

void sum_images(struct Image *image1, struct Image *image2) {
    /*
    *   Sums the byte values of each pixel in two images and stores
    *   the new values in image1.
    */
    if (image1->height != image2->height || image1->width != image2->width) {
        log_error("Images to be summed do not have equal size");
    }

    for (int y = 0; y < image1->height; y++) {
        for (int x = 0; x < image1->width; x++) {
            for (int k = 0; k < image1->pixel_width; k++) {
                int sum = image1->pixel_array[y][x][k] + image2->pixel_array[y][x][k];
                if (sum > 255) {
                    image1->pixel_array[y][x][k] = 255;
                } else {
                    image1->pixel_array[y][x][k] = (char) sum;
                }
            }
        }
    }
}

void free_image(struct Image *image) {
    for (int y = 0; y < image->height; y++) {
        for(int x = 0; x < image->width; x++) {
            free(image->pixel_array[y][x]);
        }
        free(image->pixel_array[y]);
    }
    printf("How many any\n");
}
