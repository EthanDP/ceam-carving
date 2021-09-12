#include <stdio.h>
#include <stdint.h>

#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#define NO_ERROR 0
#define INVALID_FILENAME 1

typedef uint8_t byte;

struct Image {
    FILE *image_file;
    int width;
    int height;
    int pixel_width;
    int padding;
    int error_code;
    int array_size;
    byte*** pixel_array;
};

// Error codes
#define SUCCESS 0
#define INVALID_TYPE 2

#endif