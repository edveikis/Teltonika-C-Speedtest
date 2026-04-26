#include "dataImporter.h"

FILE* data_importer_open_file(const char* filename)
{
    FILE* f  = fopen(filename, "r");

    if (!f)
    {  
        printf("[ERROR] Could not open the file\n");
        return NULL;
    }

    return f;
}

long data_importer_get_file_size(FILE* f)
{
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size < 0)
        return -1;
    rewind(f); 

    return size;
}

char* data_importer_get_buffer(FILE* f)
{
    // Get file size
    long size = data_importer_get_file_size(f);

    if (size < 0)
        return NULL;

    // Allocate buffer for data
    char *buffer = malloc(size + 1);
    if (!buffer)
    {
        printf("[ERROR] Could not allocate buffer\n");
        return NULL;
    }

    // Read file into buffer
    size_t read_size = fread(buffer, 1, size, f);
    if (read_size != size)
    {
        printf("[ERROR] Read size doesnt match size of file\n");
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';

    return buffer;
}

void data_importer_cleanup(FILE* f, char* buffer) 
{
    if (f)
        fclose(f);

    if (buffer)
        free(buffer);
}