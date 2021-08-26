#include <stdio.h>
#include <string.h>

#include "image.h"
#include "image_util.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        printf("Provided filename: %s\n", argv[1]);
        struct Image image = open_image(argv[1], strlen(argv[1]));
        if (image.error_code == 1) {
            printf("ERROR: File does not exist.\n");
            return 0;
        } else {
            write_image(image, "bmp");
        }
    } else if (argc > 2) {
        printf("ERROR: Too many arguments.");
    } else {
        printf("ERROR: No filename provided.\n");
    }
}


