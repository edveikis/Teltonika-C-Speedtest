#include "speedTest.h"

double speed_test_download(const char* url, int size)
{
    char full_url[512];

    if (size > 0)
        snprintf(full_url, sizeof(full_url), "%s/download?size=%d", url, size * 1024 * 1024);
    else
        snprintf(full_url, sizeof(full_url), "%s", url);
    
    struct Response response = {0};
    int result = http_get(full_url, &response, 1);
    
    if (result != APP_OK)
        return -1.0;

    double mbps = (response.downloadSpeed * 8.0) / 1e6;

    free(response.data);

    return mbps;
}
