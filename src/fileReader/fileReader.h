#include <stdio.h>
#include <stdlib.h>

FILE* open_file(const char* filename, const char* type);
long get_file_size(FILE* f);
char* get_buffer(FILE* f);
void cleanup(FILE* f, char* buffer);