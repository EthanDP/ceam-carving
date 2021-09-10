#include <stdio.h>
#include <string.h>

#include "byte_util.h"

int compare_string(char string1[], char string2[]) {
    if (strlen(string1) != strlen(string2)) {
        return 0;
    }

    for (int i = 0; i < sizeof(*string1); i++) {
        if (string1[i] != string2[i]) {
            return 0;
        }
    }

    return 1;
}

int bytes_to_int(char bytes[], int size, int mode) {
    // Mode 0 = Little Endian, Mode 1 = Big Endian

    unsigned int result = 0;
    unsigned int temp;

    for (int i = 0; i < size; i++) {
        if (i != 0) {
            temp = (unsigned int)(bytes[i] << (8 * i));
        }
        else {
            // For some reason requires a recast or it just stores an integer
            // for some ungodly reason (filled with 1s up until the byte for the char)
            temp = (unsigned char)bytes[i];
        }
        result += temp;
    }

    return result;
}

void printx(char bytes[], int size, int mode) {
    // Mode 0 = Litle Endian, Mode 1 = Big Endian
    if (mode == 1) {
        for (int i = size - 1; i >= 0; i--) {
            // %02 means the output will always be two characters wide
            printf("%02x", bytes[i]);
            if ((i) % 2 == 0 && i != size - 1) {
                printf(" ");
            }
        }
    } 
    else {
        for (int i = 0; i < size; i++) {
            printf("%02x", (unsigned char)bytes[i]);
            if ((i-1) % 2 == 0) {
                printf(" ");
            }
        }
    }
}

void write_blank_bytes(int total_bytes, FILE *file) {
    for (int i = 0; i < total_bytes; i++) {
        fputc(0x00, file);
    }
}
