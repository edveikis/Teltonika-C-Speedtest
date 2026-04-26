#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "cJSON.h"
#include "dataImporter.h"
#include "httpClient.h"
#include "locationService.h"

int main(int argc, char *argv[]) 
{
    cJSON *root = cJSON_CreateNull();

    int res = getLocation(&root);

    if (res != 0)
    {
        printf("[ERROR] Failed to get location of the user\n");
        return 1;
    }

    if (cJSON_IsNull(root))
    {
        printf("cJSON root is null");
        return 1;
    }

    printf("%s\n", getCountry(root));
    printf("%s\n", getCity(root));


    // int opt;
    // int download = 0;
    // int upload = 0;
    // char* server = NULL;

    // while ((opt = getopt(argc, argv, "dus:")) != -1) {
    //     switch (opt) {
    //         case 'd':
    //             download = 1;
    //             break;
    //         case 'u':
    //             upload = 1;
    //             break;
    //         case 's':
    //             server = optarg;
    //             break;
    //         default:
    //             fprintf(stderr, "Usage: %s [-d] [-u] [-s server]\n", argv[0]);
    //             return 1;
    //     }
    // }

    // FILE* f = data_importer_open_file("speedtest_server_list.json");

    // if (!f)
    //     return 1;

    // char* buffer = data_importer_get_buffer(f);

    // if (!buffer)
    // {
    //     if (f)
    //         fclose(f);
    //     return 1;
    // }

    // cJSON *json = cJSON_Parse(buffer);
    // if (!json)
    // {
    //     printf("[ERROR] Failed parsing JSON\n");
    //     data_importer_cleanup(f, buffer);
    //     return 1;
    // }

    // cJSON_Delete(json);
    // data_importer_cleanup(f, buffer);

    return 0;
}
