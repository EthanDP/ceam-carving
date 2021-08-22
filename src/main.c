#include <stdio.h>

#include "image_util/image.h"
#include "image_util/bmp.h"
#include "util/byte_helper.h"

#define BLANK 64 // ASCII @ symbol

struct Image open_image(char filename[], int size);

int main(void) {
    char filename[255] = {0};

    printf("Enter a filename: ");
    scanf("%253s", filename);

    struct Image image = open_image(filename, sizeof(filename));
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
    printf("FILENAME: %s\n", filename);
    image.image_data = fopen(filename, "rb");
    
    char extension[4] = {BLANK, BLANK, BLANK, BLANK};

    int curr_index = 3;

    for (int i = size-1; i > 0; i--) {
        if (curr_index < 0) {
            printf("Invalid Extension");
            break;
        } else if ((int)filename[i] == (int)'.') {
            break;
        } else if ((int)filename[i] != 0) {
            extension[curr_index] = filename[i];
            curr_index -= 1;
        }
    }

    // printf("Extension: %s\n", extension);

    if (compare_filetype(extension, "@bmp")) {
        read_bmp(image);
    } else {
        printf("Invalid file type");
    }


    return image;
}


