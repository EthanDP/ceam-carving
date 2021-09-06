#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "functions.h"

#include "image_util.h"
#include "byte_util.h"
#include "logging_util.h"

#include "blur.h"

void display_help();

int main(int argc, char *argv[]) {
    /*
    *   Argument handling and invalid argument logging
    */
    if (argc <= 1) {
        printf("Not enough arguments provided.");
        display_help();
    }

    struct Image image = open_image(argv[1], strlen(argv[1]));
    if (image.error_code == 1) {
        printf("ERROR: File does not exist.\n");
        return 1;
    }

    int task = NONE;
    int parameters[8] = {0};

    for (int i = 2; i < argc; i++) {
        if (compare_string("--blur", argv[i])) {
            task = BLUR;
            if (argc - i > 1 && atoi(argv[i+1]) != 0) {
                int blur_strength = atoi(argv[i+1]);
                if (blur_strength >= 1 && blur_strength <= 100) {
                    parameters[0] = blur_strength;
                } else {
                    printf("Invalid blur strength, must be 1-100.\n");
                    return 1;
                }
                
                i += 1;
            } else {
                parameters[0] = 25;
            }
        } else if (compare_string("-v", argv[i])){
            set_logging_mode(VERBOSE);
        } else {
            printf("Invalid argument %s\n", argv[i]);
            return 1;
        }
    }

    switch (task) {
        case BLUR:
            blur(&image, parameters[0]);
            write_image(&image, "bmp");
            return 0;
        
        default:
            printf("No function provided, aborting.");
            break;
    }
}

void display_help() {
    printf("usage: ceam (filename) [command] [<args>]\n\n");
    printf("Available commands:\n");
    printf("--blur [strength 1-100]: blurs the provided image (default strength = 25)\n");
    printf("-v: verbose logging\n");
}
