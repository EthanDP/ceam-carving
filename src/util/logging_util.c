#include <stdio.h>

int logging_mode = 0;

int set_logging_mode(int value) {
    /*
    *   Sets logging mode to verbose (1) or quiet (0)
    */
    logging_mode = value;
}

void log_message(char *message) {
    if (logging_mode == 0) {
        return;
    }

    printf("%s", message);
}

void log_error(char *error) {
    printf("ERROR: %s\n", error);
}
