#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <curl/curl.h>

struct Memory {
    char *data;
    size_t size;
};

int makeRequest(const char* dst, struct Memory* response);

#endif