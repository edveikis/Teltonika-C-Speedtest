#include "fileReader.h"

FILE* open_file(const char* filename)
{
    FILE* f  = fopen(filename, "r");

    if (!f)
    {  
        printf("[ERROR] Could not open the file\n");
        return NULL;
    }

    return f;
}

long get_file_size(FILE* f)
{
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f); 

    return size;
}

char* get_buffer(FILE* f)
{
    // Get file size
    long size = get_file_size(f);

    // Allocate buffer for data
    char *buffer = malloc(size + 1);
    if (!buffer)
    {
        printf("[ERROR] Could not allocate buffer\n");
        fclose(f);
        return NULL;
    }

    // Read file into buffer
    size_t read_size = fread(buffer, 1, size, f);
    if (read_size != size)
    {
        printf("[ERROR] Read size doesnt match size of file\n");
        free(buffer);
        fclose(f);
        return NULL;
    }

    buffer[size] = '\0';

    return buffer;
}

void cleanup(FILE* f, char* buffer) 
{
    fclose(f);
    free(buffer);
}