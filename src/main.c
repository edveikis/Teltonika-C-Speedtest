#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "cJSON.h"
#include "dataImporter.h"
#include "httpClient.h"

int main(int argc, char *argv[]) 
{
    struct Memory response = {0};
    int res = makeRequest("http://ip-api.com/json", &response);

    if (res != CURLE_OK)
    {
        printf("Request failed");
        return 1;
    }

    printf("%s", response.data);

    free(response.data);

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
