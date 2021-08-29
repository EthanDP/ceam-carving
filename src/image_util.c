#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "image_util.h"
#include "byte_util.h"
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
            printf("Invalid Extension\n");
            break;
        } else if ((int)filename[i] == (int)'.') {
            break;
        } else if ((int)filename[i] != 0) {
            extension[curr_index] = filename[i];
            curr_index -= 1;
        }
    }

    if (compare_string(extension, "@bmp")) {
        read_bmp(&image);
    } else {
        printf("Invalid file type.");
    }

    return image;
}

void write_image(struct Image image, char filetype[]) {
    // TODO: Check for different filetypes and call specific function accordingly
    if (compare_string(filetype, "bmp")) {
        write_bmp(image);
    } 
    // TODO: Add output checking to main.c so invalid output filetypes can't be used
}

void copy_image(struct Image *copy, struct Image original) {
    copy->width = original.width;
    copy->height = original.height;
    copy->pixel_width = original.pixel_width;
    copy->pixel_array = malloc(copy->width * sizeof(*copy->pixel_array));

    for (int i = 0; i < copy->width; i++) {
        copy->pixel_array[i] = malloc(copy->height * sizeof(*copy->pixel_array[i]));

        for (int j = 0; j < copy->height; j++) {
            copy->pixel_array[i][j] = malloc(copy->pixel_width * sizeof(*copy->pixel_array[i][j]));

            for (int k = 0; k < copy->pixel_width; k++) {
                copy->pixel_array[i][j][k] = original.pixel_array[i][j][k];
            }
        }
    }
}

void free_image(struct Image *image) {
    for (int i = 0; i < image->width; i++) {
        for(int j = 0; j < image->height; j++) {
            free(image->pixel_array[i][j]);
        }
        free(image->pixel_array[i]);
    }
    free(image->pixel_array);
}