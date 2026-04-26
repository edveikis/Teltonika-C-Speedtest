#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "cJSON.h"
#include "dataImporter.h"

int main(int argc, char *argv[]) 
{
    FILE* f = data_importer_open_file("speedtest_server_list.json");

    if (!f)
        return 1;

    char* buffer = data_importer_get_buffer(f);

    if (!buffer)
    {
        fclose(f);
        return 1;
    }

    printf("%s\n", buffer);
    
    data_importer_cleanup(f, buffer);

    return 0;
}
