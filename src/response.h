#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdlib.h>

struct Response {
    char *data;
    size_t size;
    curl_off_t uploadSize;
    curl_off_t downloadSize;
    curl_off_t us_uploadTime;
    curl_off_t downloadSpeed;
    curl_off_t uploadSpeed;
};

#endif