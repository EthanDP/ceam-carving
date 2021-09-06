#ifndef IMAGE_UTIL_HEADER
#define IMAGE_UTIL_HEADER

#define BLANK 64 // ASCII @ symbol

struct Image open_image(char filename[], int size);
void write_image(struct Image *image, char filetype[]);
void copy_image(struct Image *copy, struct Image original);
void free_image(struct Image *image);

#endif
