#ifndef LOCATION_SERVICE_H
#define LOCATION_SERVICE_H

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "../memory.h"
#include "../http/httpClient.h"
#include "../lib/cjson/cJSON.h"

int getLocation(cJSON** root);
char* getCity(cJSON* root);
char* getCountry(cJSON* root);

#endif