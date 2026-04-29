#ifndef BEST_SERVER_H
#define BEST_SERVER_H

#include "../http/httpClient.h"
#include "../cjson/cJSON.h"
#include "../helpers/helpers.h"
#include "../dataImporter/dataImporter.h"
#include "../locationService/locationService.h"

char* best_server_get(const char* speed_test_file);


#endif