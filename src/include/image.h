#include <stdio.h>

#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#define NO_ERROR 0
#define INVALID_FILENAME 1

struct Image {
    FILE *image_file;
    int width;
    int height;
    int pixel_width;
    int padding;
    int error_code;
    int array_size;
    unsigned char*** pixel_array;
};

#endif