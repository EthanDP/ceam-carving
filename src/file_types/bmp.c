#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "image.h"
#include "byte_util.h"
#include "logging_util.h"

void read_bmp(struct Image *bmp_image) {
    /*
    * Reads a bmp bmp_image and stores width, height, and pixel data
    * in an Image struct.
    *
    * bmp_image: an Image struct containing a file
    */
    
    FILE *bmp_data = bmp_image->image_file;
    log_message("Reading bmp image to memory...\n");

    fseek(bmp_data, 0, SEEK_SET);
    byte bmp_identifier[2];
    fread(bmp_identifier, sizeof(byte), 2, bmp_data);

    if (bmp_identifier[0] != 0x42 && bmp_identifier[1] != 0x4d) {
        log_error("Invalid bmp file identifier");
        bmp_image->error_code = INVALID_TYPE;
        return;
    }

    fseek(bmp_data, 10, SEEK_SET);
    byte offset_hex[4];
    fread(offset_hex, sizeof(offset_hex), 1, bmp_data);
    int offset = bytes_to_int(offset_hex, sizeof(offset_hex), LE);

    byte header_size[4];
    fread(header_size, sizeof(byte), 4, bmp_data);

    byte hex_width[4];
    fread(hex_width, sizeof(byte), 4, bmp_data);

    byte hex_height[4];
    fread(hex_height, sizeof(byte), 4, bmp_data);

    bmp_image->width = bytes_to_int(hex_width, sizeof(hex_width), LE);
    bmp_image->height = bytes_to_int(hex_height, sizeof(hex_height), LE);

    // TODO: Modify pixel width based off of header
    bmp_image->pixel_width = 3;

    int padding;
    
    if (bmp_image->width % 4 == 0) {
        padding = 0;
    } else {
        padding = 4 - ((bmp_image->width * bmp_image->pixel_width) % 4); 
    }

    bmp_image->padding = padding;    

    // Accessing and storing pixels
    byte *pixel;
    pixel = malloc(bmp_image->pixel_width * sizeof(byte));
    int array_size = 0;

    fseek(bmp_data, offset, SEEK_SET);
    bmp_image->pixel_array = malloc(bmp_image->height * sizeof(*bmp_image->pixel_array));

    /* Pixel array structured as follows:
    *   [[pixel, pixel, pixel],
    *   [pixel, pixel, pixel],
    *   [pixel, pixel, pixel]]
    * 
    *   First index value refers to y coordinate (i.e. row)
    *   Second index value refers to x coordinate (i.e. column)
    * 
    *   pixel_array[y][x][byte]
    */

    for (int y = 0; y < bmp_image->height; y++) {
        bmp_image->pixel_array[y] = malloc(bmp_image->width * sizeof(*bmp_image->pixel_array[y]));

        for (int x = 0; x < bmp_image->width; x++) {
            bmp_image->pixel_array[y][x] = malloc(bmp_image->pixel_width * sizeof(*bmp_image->pixel_array[y][x]));
            fread(pixel, sizeof(byte), 3, bmp_data);

            for (int byte_idx = 0; byte_idx < bmp_image->pixel_width; byte_idx++) {
                bmp_image->pixel_array[y][x][byte_idx] = pixel[byte_idx];
                array_size++;
            }
        }

        fseek(bmp_data, padding, SEEK_CUR);
    }

    bmp_image->array_size = array_size;

    free(pixel);
    fclose(bmp_image->image_file);

    log_message("Bmp image read successfully\n");
}

void write_bmp(struct Image *image) {
    /*
    * Writes to a specified file the contents of bmp_image.
    *
    * bmp_image: an Image struct containing information about the bmp_image to write
    */

    log_message("Writing result to bmp...\n");

    FILE *file;
    file = fopen("result.bmp", "wb");

    /*
    * BMP File Header
    */
    // Writes the default header field used to identify a bmp
    fputc(0x42, file);
    fputc(0x4D, file);
    // Placehold for size of BMP file
    unsigned int size = image->array_size + 54;
    for(int i = 0; i < INT_BYTE_SIZE; i++) {
        fputc((size >> (i * 8)) & 0xFF, file);
    }
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

    printf("That width at this point: %i\n", image->width);

    for(int i = 0; i < INT_BYTE_SIZE; i++) {
        fputc(image->width >> i * 8 & 0xFF, file);
    }
    // Height
    printf("That height at this point: %i\n", image->height);
    for(int i = 0; i < INT_BYTE_SIZE; i++) {
        fputc(image->height >> i * 8 & 0xFF, file);
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
    
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            for (int byte_idx = 0; byte_idx < image->pixel_width; byte_idx++) {
                fputc(image->pixel_array[y][x][byte_idx], file);
            }
        }
        write_blank_bytes(image->padding, file);
    }

    fclose(file);
    log_message("Result written successfully\n");
}
