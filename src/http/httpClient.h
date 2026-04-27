#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <curl/curl.h>

#include "../response.h"

/// @brief Makes an HTTP request
/// @param dst domain to make request to
/// @param response response data and size stored here
/// @return response code
int http_make_request(const char* dst, struct Response* response);

#endif