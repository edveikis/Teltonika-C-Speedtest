#include "helpers.h"

int add_string(char ***list, size_t *size, size_t *capacity, const char *str) 
{
    if (*size == *capacity) 
    {
        size_t new_capacity = (*capacity == 0) ? 4 : (*capacity * 2);

        char **tmp = realloc(*list, new_capacity * sizeof(char *));

        if (!tmp) 
            return 0;

        *list = tmp;
        *capacity = new_capacity;
    }

    (*list)[*size] = strdup(str);

    if (!(*list)[*size]) 
        return 0;

    (*size)++;

    return APP_OK;
}


void free_string_list(char **list, size_t size)
 {
    if (!list) 
        return;

    for (size_t i = 0; i < size; i++) 
    {
        free(list[i]);
    }

    free(list);
}