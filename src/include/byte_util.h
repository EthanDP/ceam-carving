#ifndef BYTE_UTIL_HEADER
#define BYTE_UTIL_HEADER

#define FILETYPE_LENGTH 4
#define LE 0
#define BE 1

#define INT_BYTE_SIZE (sizeof(int)/sizeof(char))
#define BYTE_SIZE 8

int compare_filetype(char string1[], char string2[]);
int bytes_to_int(char bytes[], int size, int mode);
void printx(char bytes[], int size, int mode);
void write_blank_bytes(int total_bytes, FILE *file);

#endif