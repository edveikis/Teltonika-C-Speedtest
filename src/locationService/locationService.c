#include "locationService.h"

int getLocation(cJSON** root)
{
    struct Memory response = {0};
    int res = makeRequest("http://ip-api.com/json/\?fields\=status,message,country,city", &response);

    if (res != CURLE_OK)
    {
        printf("Request to API failed: %s\n", curl_easy_strerror(res));
        return 1;
    }

    *root = cJSON_Parse(response.data);

    if (!*root)
    {
        printf("[ERROR] JSON root was NULL");
        free(response.data);
        response.data = NULL;
        response.size = 0;
        return 1;
    }

    cJSON* status = cJSON_GetObjectItem(*root, "status");
    
    if (!cJSON_IsString(status))
    {
        printf("[ERROR] Unknown/missing format");
        cJSON_Delete(*root);
        free(response.data);
        return 1;
    }

    if (strcmp(status->valuestring, "success") != 0)
    {
        cJSON* message = cJSON_GetObjectItem(*root, "message");
        printf("[ERROR] API request for location data failed: %s\n", 
        cJSON_IsString(message) ? message->valuestring : "Unknown message");
        cJSON_Delete(*root);
        free(response.data);
        response.data = NULL;
        response.size = 0;
        return 1;
    }

    free(response.data);
    response.data = NULL;
    response.size = 0;

    return 0;
}

char* getCity(cJSON* root)
{
    if (!root)
        return NULL;

    cJSON* city = cJSON_GetObjectItem(root, "city");

    if (!cJSON_IsString(city))
        return NULL;

    return city->valuestring;
}

char* getCountry(cJSON* root)
{
    if (!root)
        return NULL;

    cJSON* country = cJSON_GetObjectItem(root, "country");

    if (!cJSON_IsString(country))
        return NULL;

    return country->valuestring;
}