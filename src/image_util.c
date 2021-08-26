#include <stdio.h>

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