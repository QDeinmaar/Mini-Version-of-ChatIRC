#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void log_error(const char* msg) {
        fprintf(stderr, "Error: %s\n", msg);
    }

void log_infos(const char* msg) {
        fprintf(stderr, "Info: %s\n", msg);
    }


