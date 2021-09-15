#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "image_util.h"
#include "logging_util.h"
#include "kernel.h"
#include "functions.h"

Kernel create_edge_kernel();

void detect_edges(struct Image *image) {
    Kernel edge_kernel = create_edge_kernel();
    log_message("Detecting edges...\n");

    apply_kernel(image, edge_kernel, EDGE_DETECT);
}

Kernel create_edge_kernel() {
    
    Kernel edge_kernel;
    edge_kernel.size = 3;

    double kernel_array[3][3] = {
        {-.25, 0.0, .25},
        {-.5, 0.0, .5},
        {-.25, 0.0, .25}
    };

    edge_kernel.kernel_array = malloc(edge_kernel.size * sizeof(*edge_kernel.kernel_array));

    for (int y = 0; y < edge_kernel.size; y++) {
        edge_kernel.kernel_array[y] = malloc(edge_kernel.size * sizeof(*edge_kernel.kernel_array[y]));
        for (int x = 0; x < edge_kernel.size; x++) {
            edge_kernel.kernel_array[y][x] = kernel_array[y][x];
        }
    }

    return edge_kernel;
}