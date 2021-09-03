#include <stdio.h>
#include <string.h>

#include "image.h"
#include "image_util.h"
#include "byte_util.h"
#include "blur.h"

void display_help();

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Not enough arguments provided.");
        display_help();
    }

    struct Image image = open_image(argv[1], strlen(argv[1]));
    if (image.error_code == 1) {
        printf("ERROR: File does not exist.\n");
        return 0;
    }
    
    for (int i = 2; i < argc; i++) {
        if (compare_string("--blur", argv[i])) {
            blur(&image, 25);
            write_image(&image, "bmp");
            return 0;
        } else {
            printf("Invalid argument %s", argv[i]);
            return 0;
        }
    }
}

void display_help() {
    printf("usage: ceam (filename) [command] [<args>]\n\n");
    printf("Available commands:\n");
    printf("--blur [strength 1-100]: blurs the provided image (default strength = 25)\n");
}


