#include <stdio.h>

#ifndef IMAGE_HEADER
#define IMAGE_HEADER

struct Image {
    FILE *image_data;
    int width;
    int height;
    int pixel_width;
    unsigned char*** pixel_array;
};

#endif