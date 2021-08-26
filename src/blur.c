#include <stdlib.h>

#include "image.h"
#include "kernel.h"

void blur (struct Image image) {
    /*
    *   Gaussian blur
    */

    Kernel gaussian_kernel;
    gaussian_kernel.kernel_array = malloc(3 * sizeof(*gaussian_kernel.kernel_array));
    for (int i = 0; i < 3; i++) {
        gaussian_kernel.kernel_array[i] = malloc(sizeof(*gaussian_kernel.kernel_array[i]));
        for (int j = 0; j < 3; j++) {
            gaussian_kernel.kernel_array[i][j] = .1;
        }
    }
}