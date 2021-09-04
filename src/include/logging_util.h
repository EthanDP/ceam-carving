#ifndef LOGGING_UTIL_HEADER
#define LOGGING_UTIL_HEADER

#define VERBOSE 1
#define QUIET 0

int set_logging_mode(int value);
void log_message(char *message);

#endif
