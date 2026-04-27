#ifndef SPEEDTEST_H
#define SPEEDTEST_H

#include "../enum.h"
#include "../response.h"
#include "../http/httpClient.h"

double speed_test_download(const char* url, int size);

double speed_test_upload(const char* url, int size);

#endif