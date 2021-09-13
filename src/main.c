#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "functions.h"

#include "image_util.h"
#include "byte_util.h"
#include "logging_util.h"

#include "blur.h"
#include "sharpen.h"

void display_help();

int main(int argc, char *argv[]) {
    /*
    *   Argument handling and invalid argument logging
    */
    if (argc <= 1) {
        log_error("Not enough arguments provided.");
        display_help();
    }

    int task = NONE;
    int parameters[8];

    for (int i = 2; i < argc; i++) {
        if (compare_string("--blur", argv[i])) {
            task = BLUR;
            if (argc - i > 1 && atoi(argv[i+1]) != 0) {
                int blur_strength = atoi(argv[i+1]);
                if (blur_strength >= 1 && blur_strength <= 100) {
                    parameters[0] = blur_strength;
                } else {
                    log_error("Invalid blur strength, must be 1-100.");
                    return 1;
                }
                
                i += 1;
            } else {
                parameters[0] = 25;
                continue;
            }

            if (argc - i >= 1 && atoi(argv[i+1]) != 0) {
                int blur_size = atoi(argv[i+1]);
                if (blur_size >= 1 && blur_size <= 100) {
                    parameters[1] = blur_size;
                } else {
                    log_error("Invalid blur size, must be 1-100.");
                    return 1;
                }
                
                i += 1;
            } else {
                parameters[1] = 5;
                continue;
            }
        } else if (compare_string("--sharpen", argv[i])) {
            task = SHARPEN;
            if (argc - i > 1 && atoi(argv[i+1]) != 0) {
                int sharpen_strength = atoi(argv[i+1]);
                if (sharpen_strength >= 1 && sharpen_strength <= 100) {
                    parameters[0] = sharpen_strength;
                } else {
                    log_error("Invalid sharpen strength, must be 1-100.");
                    return 1;
                }
                
                i += 1;
            } else {
                parameters[0] = 5;
                continue;
            }

            if (argc - i >= 1 && atoi(argv[i+1]) != 0) {
                int sharpen_size = atoi(argv[i+1]);
                if (sharpen_size >= 1 && sharpen_size <= 10) {
                    parameters[1] = sharpen_size;
                } else {
                    log_error("Invalid sharpen size, must be 1-10.");
                    return 1;
                }
                
                i += 1;
            } else {
                parameters[1] = 5;
                continue;
            }
        } else if (compare_string("-v", argv[i])){
            set_logging_mode(VERBOSE);
        } else if (compare_string("--convert", argv[i])) {
            task = CONVERT;
        } else {
            log_error("Invalid argument");
            display_help();
            return 1;
        }
    }

    struct Image image = open_image(argv[1], strlen(argv[1]));
    if (image.error_code == 1) {
        log_error("ERROR: File does not exist.");
        return 1;
    }

    switch (task) {
        case BLUR:
            blur(&image, parameters[0], parameters[1]);
            write_image(&image, "bmp");
            return 0;
        
        case SHARPEN:
            sharpen(&image, parameters[0], parameters[1]);
            write_image(&image, "bmp");
            return 0;

        case CONVERT:
            write_image(&image, "bmp");
            return 0;

        default:
            log_error("ERROR: No function provided, aborting.");
            return 1;
    }
}

void display_help() {
    printf("usage: ceam (filename) [command] [<args>]\n\n");
    printf("Available commands:\n");
    printf("--blur [strength 1-100] [size 1-100]: blurs the provided image (default strength = 25)\n");
    printf("-v: verbose logging\n");
}
