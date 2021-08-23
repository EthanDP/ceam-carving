#ifndef BYTE_HELPER_HEADER
#define BYTE_HELPER_HEADER

#define FILETYPE_LENGTH 4
#define LE 0
#define BE 1

#define INT_SIZE (sizeof(int)/sizeof(char))

int compare_filetype(char string1[], char string2[]);
int bytes_to_int(char bytes[], int size, int mode);
void printx(char bytes[], int size, int mode);

#endif