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

double speed_test_upload(const char* url, int size)
{
    char full_url[512];

    snprintf(full_url, sizeof(full_url), "%s/upload.php", url);

    struct Response response = {0};

    int uploadSize = size * 1024 * 1024;

    char* data;

    data = malloc(uploadSize);

    memset(data, 'A', uploadSize);

    int result = http_post(full_url, &response, data, uploadSize, 1);
    
    if (result != APP_OK)
    {
        free(data);
        return -1.0;
    }

    double mbps = (response.uploadSpeed * 8.0) / 1e6;

    free(data);
    free(response.data);

    return mbps;
}
