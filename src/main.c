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
        if (f)
            fclose(f);
        return 1;
    }

    cJSON *json = cJSON_Parse(buffer);
    if (!json)
    {
        printf("[ERROR] Failed parsing JSON\n");
        data_importer_cleanup(f, buffer);
        return 1;
    }

    cJSON_Delete(json);
    data_importer_cleanup(f, buffer);

    return 0;
}
