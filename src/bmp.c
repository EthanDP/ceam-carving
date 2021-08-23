#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "image.h"
#include "byte_helper.h"

void read_bmp(struct Image *bmp_image) {
    /*
    * Reads a bmp bmp_image and stores width, height, and pixel data
    * in an Image struct.
    *
    * bmp_image: an Image struct containing a file
    */
    
    FILE *bmp_data = bmp_image->image_file;

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

    bmp_image->width = bytes_to_int(hex_width, sizeof(hex_width), LE);
    bmp_image->height = bytes_to_int(hex_height, sizeof(hex_height), LE);

    // TODO: Modify pixel width based off of header
    bmp_image->pixel_width = 3;

    int padding;
    
    if (bmp_image->width % 4 == 0) {
        padding = 0;
    } else {
        padding = 4 - ((bmp_image->width * 3) % 4); 
    }

    // Logging
    printf("Offset: %i\n", offset);
    printf("Width: %i\n", bmp_image->width);
    printf("Height: %i\n", bmp_image->height);
    printf("Bytes per pixel: %i\n", bmp_image->pixel_width);

    // Accessing and storing pixels
    unsigned char pixel[bmp_image->pixel_width];

    fseek(bmp_data, offset, SEEK_SET);
    bmp_image->pixel_array = malloc(bmp_image->width * sizeof(unsigned char));

    for (int i = 0; i < bmp_image->width; i++) {
        bmp_image->pixel_array[i] = malloc(bmp_image->height * sizeof(unsigned char));

        for (int j = 0; j < bmp_image->height; j++) {
            bmp_image->pixel_array[i][j] = malloc(bmp_image->pixel_width * sizeof(unsigned char));
            fread(pixel, sizeof(pixel), 1, bmp_data);

            // TODO: Modify for different size bmp pixels (16 bit, 8bit, etc.)
            for (int k = 0; k < bmp_image->pixel_width; k++) {
                bmp_image->pixel_array[i][j][k] = pixel[k];
            }
        }

        fseek(bmp_data, padding, SEEK_CUR);
    }

    fclose(bmp_image->image_file);
}

void write_bmp(struct Image image) {
    /*
    * Writes to a specified file the contents of bmp_image.
    *
    * bmp_image: an Image struct containing information about the bmp_image to write
    */
    FILE *file;
    file = fopen("result.bmp", "wb");

    /*
    * BMP File Header
    */
    // Writes the default header field used to identify a bmp
    fputc(0x42, file);
    fputc(0x4D, file);
    // Placehold for size of BMP file
    fputc(0x55, file);
    fputc(0x0F, file);
    write_blank_bytes(2, file);
    // Reserved
    write_blank_bytes(4, file);
    // Offset of pixel array (aka bmp data)
    fputc(0x36, file);
    write_blank_bytes(3, file);

    /*
    * BMP Info Header
    */
    // Info Header size (40 bytes)
    fputc(0x28, file);
    write_blank_bytes(3, file);
    // Width
    // TODO: Probably could move this to byte_helper
    // TODO: Check if system is big or little endian
    for(int i = INT_BYTE_SIZE; i > 0; i--) {
        fputc(image.width >> i * 8 & 0xFF, file);
    }
    // Height
    for(int i = INT_BYTE_SIZE; i > 0; i--) {
        fputc(image.height >> i * 8 & 0xFF, file);
    }
    // TODO: Probably could move this to byte_helper
    // TODO: Check if system is big or little endian
    // Number of planes (should always be 1)
    fputc(0x01, file);
    fputc(0x00, file);
    // Bits per pixel
    fputc(0x18, file);
    fputc(0x00, file);
    // Compression (None used)
    write_blank_bytes(4, file);
    // Image size (only set if compression is enabled)
    write_blank_bytes(4, file);
    // Horizontal resolution
    fputc(0x23, file);  // idk what the significance of these values is
    fputc(0x2E, file);  // but it's what's used in bmps made in gimp
    write_blank_bytes(2, file);
    // Vertical resolution
    fputc(0x23, file);
    fputc(0x2E, file);
    write_blank_bytes(2, file);
    // Colors used (16M for 24 bit)
    fputc(0x00, file);
    fputc(0x24, file);
    fputc(0xF4, file);
    fputc(0x00, file);
    // Important Colors
    write_blank_bytes(4, file);

    /*
    * Image data
    */
    int pixel_row_size = image.width * image.pixel_width;
    int padding_size = ceil(pixel_row_size * BYTE_SIZE / 32.0) * 4 - pixel_row_size;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                fputc(image.pixel_array[i][j][k], file);
            }
        }
        write_blank_bytes(padding_size, file);
    }
    fclose(file);
}