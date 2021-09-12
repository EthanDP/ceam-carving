#ifndef BYTE_UTIL_HEADER
#define BYTE_UTIL_HEADER

#include "image.h"

#define FILETYPE_LENGTH 4
#define LE 0
#define BE 1

#define INT_BYTE_SIZE sizeof(int)
#define BYTE_SIZE 8

int compare_string(char string1[], char string2[]);
int bytes_to_int(byte bytes[], int size, int mode);
void printx(byte bytes[], int size, int mode);
void write_blank_bytes(int total_bytes, FILE *file);

#endif