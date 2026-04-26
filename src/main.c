#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "cJSON.h"
#include "fileReader.h"

int main(int argc, char *argv[]) 
{
    FILE* f = open_file("speedtest_server_list.json", "r");

    if (f == NULL)
        return 1;

    char* buffer = get_buffer(f);

    if (buffer == NULL)
        return 1;

    printf("%s\n", buffer);

    cleanup(f, buffer);

    return 0;
}
