#include <stdlib.h>
#include <stdio.h>

#include "image.h"
#include "byte_helper.h"

void read_bmp(struct Image bmp_image) {
    /*
    * Reads a bmp bmp_image and stores width, height, and pixel data
    * in an Image struct.
    *
    * bmp_image: an Image struct containing a file
    */
    
    FILE *bmp_data = bmp_image.image_data;

    fseek(bmp_data, 10, SEEK_SET);
    unsigned char offset_hex[4];
    fread(offset_hex, sizeof(offset_hex), 1, bmp_data);
    int offset = bytes_to_int(offset_hex, sizeof(offset_hex), LE);

    unsigned char header_size[4];
    fread(header_size, sizeof(header_size), 1, bmp_data);

    unsigned char hex_width[4];
    fread(hex_width, sizeof(hex_width), 1, bmp_data);
    unsigned char hex_height[4];
    fread(hex_height, sizeof(hex_height), 1, bmp_data);

    bmp_image.width = bytes_to_int(hex_width, sizeof(hex_width), LE);
    bmp_image.height = bytes_to_int(hex_height, sizeof(hex_height), LE);

    // TODO: Modify pixel width based off of header
    bmp_image.pixel_width = 3;

    int padding;
    
    if (bmp_image.width % 4 == 0) {
        padding = 0;
    } else {
        padding = 4 - ((bmp_image.width * 3) % 4); 
    }

    // Logging
    printf("Offset: %i\n", offset);
    printf("Width: %i\n", bmp_image.height);
    printf("Height: %i\n", bmp_image.height);
    printf("Pixel Width: %i\n", bmp_image.pixel_width);

    // Accessing and storing pixels

    unsigned char pixel[bmp_image.pixel_width];

    fseek(bmp_data, offset, SEEK_SET);
    bmp_image.pixel_array = malloc(bmp_image.width * sizeof(unsigned char));

    for (int i = 0; i < bmp_image.width; i++) {
        bmp_image.pixel_array[i] = malloc(bmp_image.height * sizeof(unsigned char));

        for (int j = 0; j < bmp_image.height; j++) {
            bmp_image.pixel_array[i][j] = malloc(bmp_image.pixel_width * sizeof(unsigned char));
            fread(pixel, sizeof(pixel), 1, bmp_data);
            printx(pixel, sizeof(pixel), LE);
            printf("\n");

            // TODO: Modify for different size bmp pixels (16 bit, 8bit, etc.)
            for (int k = 0; k < bmp_image.pixel_width; k++) {
                bmp_image.pixel_array[i][j][k] = pixel[k];
            }
        }

        fseek(bmp_data, padding, SEEK_CUR);
    }
}

void write_bmp(struct Image image) {
    /*
    * Writes to a specified file a bmp bmp_image.
    *
    * bmp_image: an Image struct containing information about the bmp_image to write
    */
    printf("Writing");
}