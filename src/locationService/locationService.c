#include "locationService.h"

int location_service_get(cJSON** root)
{
    struct Response response = {0};
    int res = http_get("http://ip-api.com/json/\?fields\=status,message,country,city", &response, 0);

    if (res != APP_OK)
    {
        printf("Request to API failed: %s\n", curl_easy_strerror(res));
        return APP_REQUEST_FAILED;
    }

    *root = cJSON_Parse(response.data);

    if (!*root)
    {
        printf("[ERROR] JSON root was NULL");
        free(response.data);
        response.data = NULL;
        response.size = 0;
        return APP_INVALID_JSON;
    }

    cJSON* status = cJSON_GetObjectItem(*root, "status");
    
    if (!cJSON_IsString(status))
    {
        printf("[ERROR] Unknown/missing format");
        cJSON_Delete(*root);
        free(response.data);
        return APP_INVALID_FORMAT;
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
        return APP_API_FAILURE;
    }

    free(response.data);
    response.data = NULL;
    response.size = 0;

    return APP_OK;
}

char* location_service_get_city(cJSON* root)
{
    if (!root)
        return NULL;

    cJSON* city = cJSON_GetObjectItem(root, "city");

    if (!cJSON_IsString(city))
        return NULL;

    return city->valuestring;
}

char* location_service_get_country(cJSON* root)
{
    if (!root)
        return NULL;

    cJSON* country = cJSON_GetObjectItem(root, "country");

    if (!cJSON_IsString(country))
        return NULL;

    return country->valuestring;
}