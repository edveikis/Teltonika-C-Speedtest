#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <curl/curl.h>
#include<string.h>

#include "../response.h"
#include "../enum.h"

/// @brief Makes a get request to specific url
/// @param dst url to make request o
/// @param response response data
/// @return status code
int http_get(const char* dst, struct Response* response, int discard);

/// @brief Makes a post reqeuest to specific url
/// @param dst url to make request to
/// @param response response data
/// @param data data to be sent
/// @param size size of data being sent
/// @return status code
int http_post(const char* dst, struct Response* response, const void* data, size_t size, int discard);


#endif