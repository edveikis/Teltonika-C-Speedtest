#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdlib.h>

/// @brief Opens file for reading data
/// @param filename file name
/// @return FILE instance
FILE* data_importer_open_file(const char* filename);

/// @brief Gets file size
/// @param f FILE instance
/// @return file size
long data_importer_get_file_size(FILE* f);

/// @brief Returns char* data buffer read from file
/// @param f File instance
/// @return data buffer
char* data_importer_get_buffer(FILE* f);

/// @brief Cleans up allocated memory
/// @param f FILE instance
/// @param buffer data buffer
void data_importer_cleanup(FILE* f, char* buffer);

#endif