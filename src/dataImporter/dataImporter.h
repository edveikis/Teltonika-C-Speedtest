#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdlib.h>

FILE* data_importer_open_file(const char* filename);
long data_importer_get_file_size(FILE* f);
char* data_importer_get_buffer(FILE* f);
void data_importer_cleanup(FILE* f, char* buffer);

#endif