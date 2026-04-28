#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <string.h>

#include "../enum.h"

int add_string(char ***list, size_t *size, size_t *capacity, const char *str);

void free_string_list(char **list, size_t size);

#endif