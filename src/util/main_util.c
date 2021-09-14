#include <stdlib.h>

#include "image.h"
#include "image_util.h"

#include "logging_util.h"

#include "functions.h"
#include "blur.h"
#include "sharpen.h"
#include "mushroomify.h"

void run_task(char filename[], int parameters[], int task, int length) {
    struct Image image = open_image(filename, length);
    if (image.error_code == 1) {
        log_error("ERROR: File does not exist.");
        exit(0);
    }

    switch (task) {
        case BLUR:
            blur(&image, parameters[0], parameters[1]);
            write_image(&image, "bmp");
            return;
        
        case SHARPEN:
            sharpen(&image, parameters[0], parameters[1]);
            write_image(&image, "bmp");
            return;

        case CONVERT:
            write_image(&image, "bmp");
            return;

        case MUSHROOMIFY:
            mushroomify(&image, parameters[0]);
            write_image(&image, "bmp");
            return;

        default:
            log_error("ERROR: No function provided, aborting.");
            return;
    }
}