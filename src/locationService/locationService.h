#ifndef LOCATION_SERVICE_H
#define LOCATION_SERVICE_H

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "../response.h"
#include "../http/httpClient.h"
#include "../lib/cjson/cJSON.h"

/// @brief Gets user location and stores it in json format in root
/// @param root address to root ptr that stores json data
/// @return status code
int getLocation(cJSON** root);

/// @brief Gets user's city string from JSON root
/// @param root JSON root with data
/// @return City name string
char* getCity(cJSON* root);

/// @brief Gets user's country string from JSON root
/// @param root JSON root with data
/// @return Country name string
char* getCountry(cJSON* root);

#endif