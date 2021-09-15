#ifndef KERNEL_HEADER
#define KERNEL_HEADER

typedef struct Kernels {
    double **kernel_array;
    int size;
} Kernel;

void apply_kernel(struct Image *image, Kernel kernel, int mode);

#endif