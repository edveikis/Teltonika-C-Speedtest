#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "cJSON.h"
#include "dataImporter.h"
#include "httpClient.h"
#include "locationService.h"
#include "speedTest.h"
#include "helpers.h"
#include "bestServer.h"

int main(int argc, char *argv[]) 
{
    int auto_mode = 0;
    int download = 0;
    int upload = 0;
    int best_server = 0;
    char *server = NULL;

    int opt;

    while ((opt = getopt(argc, argv, "adubs:")) != -1)
    {
        switch (opt)
        {
            case 'a':
                auto_mode = 1;
                break;

            case 'd':
                download = 1;
                break;

            case 'u':
                upload = 1;
                break;

            case 'b':
                best_server = 1;
                break;

            case 's':
                server = optarg;
                break;

            default:
                return 1;
        }
    }

    if (!auto_mode && !download && !upload && !best_server)
    {
        fprintf(stderr, "No action specified\n");
        return 1;
    }

    if ((download || upload) && !server)
    {
        fprintf(stderr, "Download/upload requires -s <server>\n");
        return 1;
    }

    if (auto_mode)
    {
        printf("Running full automatic test...\n");

        printf("Looking for the best server...\n");

        char *best = best_server_get("speedtest_server_list.json");

        if (!best)
        {
            fprintf(stderr, "Failed to find best server\n");
            return 1;
        }

        printf("Best server found: %s\n", best);

        printf("Running download test...\n");

        double mbps = speed_test_download(best, 100);

        printf("Download speed: %f mbps\n", mbps);
        

        printf("Running upload test...\n");
            
        mbps = speed_test_upload(best, 100);

        printf("Upload speed: %f mbps\n", mbps);

        free(best);
    }
    else
    {
        if (best_server)
        {
            char *best = best_server_get("speedtest_server_list.json");

            if (!best)
            {
                fprintf(stderr, "Failed to find best server\n");
                return APP_ERROR;
            }

            printf("Best server: %s\n", best);
            free(best);
        }

        if (download)
        {
            printf("Running download test on: %s\n", server);

            double mbps = speed_test_download(server, 100);

            printf("Download speed: %f mbps\n", mbps);
        }

        if (upload)
        {
            printf("Running upload test on: %s\n", server);
            
            double mbps = speed_test_upload(server, 100);

            printf("Upload speed: %f mbps\n", mbps);
        }
    }

    return APP_OK;
}
