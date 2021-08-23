#include <stdio.h>
#include <string.h>

#include "image.h"
#include "bmp.h"
#include "byte_helper.h"

#define BLANK 64 // ASCII @ symbol

struct Image open_image(char filename[], int size);

int main(int argc, char *argv[]) {
    if (argc == 2) {
        printf("Provided filename: %s\n", argv[1]);
        struct Image image = open_image(argv[1], strlen(argv[1]));
        if (image.error_code == 1) {
            printf("ERROR: File does not exist.\n");
        }
        write_bmp(image);
    } else {
        printf("ERROR: No filename provided.\n");
    }
}

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

    if (compare_filetype(extension, "@bmp")) {
        read_bmp(&image);
    } else {
        printf("Invalid file type");
    }

    return image;
}


