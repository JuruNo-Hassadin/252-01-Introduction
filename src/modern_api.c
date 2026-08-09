#include "api_bridge_lab.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int modern_parse_year(const char* record, int* out_year) {
    const char* colon;
    const char* year_text;
    char* end;
    long year;

    if (record == NULL || out_year == NULL) {
        return -1;
    }

    colon = strchr(record, ':');
    if (colon == NULL) {
        return -1;
    }

    year_text = colon + 1;
    errno = 0;

    year = strtol(year_text, &end, 10);

   
    if (end == year_text) {
        return -1;
    }

    
    if (*end != '\0') {
        return -1;
    }

   
    if (errno == ERANGE) {
        return -1;
    }

    
    if (year < INT_MIN || year > INT_MAX) {
        return -1;
    }

    *out_year = (int)year;
    return 0;
}

int modern_make_slug(const char* name, char* out, size_t out_size) {
    size_t i;

    if (name == NULL || out == NULL || out_size == 0) {
        return -1;
    }

    for (i = 0; name[i] != '\0' && i + 1 < out_size; i++) {
        if (name[i] == ' ') {
            out[i] = '_';
        }
        else {
            out[i] = (char)tolower((unsigned char)name[i]);
        }
    }

   
    if (name[i] != '\0') {
        return -1;
    }

    out[i] = '\0';
    return 0;
}