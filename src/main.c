#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "cJSON.h"

int main(int argc, char *argv[]) 
{
    FILE *f  = fopen("speedtest_server_list.json", "r");

    if (!f)
    {  
        printf("[ERROR] Could not open the file\n");
        return 1;
    }

    // Get file size
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f); 

    // Allocate buffer for data
    char *buffer = malloc(size + 1);
    if (!buffer)
    {
        printf("[ERROR] Could not allocate buffer\n");
        fclose(f);
        return 1;
    }

    // Read file into buffer
    size_t read_size = fread(buffer, 1, size, f);
    if (read_size != size)
    {
        printf("[ERROR] Read size doesnt match size of file\n");
        free(buffer);
        fclose(f);
        return 1;
    }

    buffer[size] = '\0';

    fclose(f);

    printf("%s\n", buffer);

    return 0;
}
