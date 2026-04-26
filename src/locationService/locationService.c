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
        return 1;
    }

    char* status = cJSON_GetObjectItem(*root, "status")->valuestring;
    if (strcmp(status, "success") != 0)
    {
        printf("[ERROR] API request for location data failed: %s\n", 
        cJSON_GetObjectItem(*root, "message")->valuestring);
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

    return cJSON_GetObjectItem(root, "city")->valuestring;
}

char* getCountry(cJSON* root)
{
    if (!root)
        return NULL;

    return cJSON_GetObjectItem(root, "country")->valuestring;
}