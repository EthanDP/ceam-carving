#include <stdio.h>
#include <string.h>

#include "byte_helper.h"

int compare_filetype(char input[], char filetype[]) {
    for (int i = 0; i < FILETYPE_LENGTH; i++) {
        if (input[i] != filetype[i]) {
            return 0;
        }
    }
    return 1;
}

int compare_string(char *string1[], char *string2[]) {
    if (sizeof(*string1) != sizeof(*string2)) {
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

    int result = 0;
    int temp;

    for (int i = 0; i < size; i++) {
        if (i != 0) {
            temp = (int)bytes[i] * (256 * i);
        }
        else {
            temp = (int)bytes[i];
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