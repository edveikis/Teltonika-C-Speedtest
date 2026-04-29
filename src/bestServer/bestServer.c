#include "bestServer.h"

int split_servers_by_country(
    cJSON *root,
    const char *target_country,
    char ***listCountry, size_t *sizeCountry, size_t *capacityCountry,
    char ***list, size_t *size, size_t *capacity)
{
    if (!root || !cJSON_IsArray(root))
        return APP_INVALID_JSON;

    cJSON *server;
    cJSON_ArrayForEach(server, root) {
        const char *country = cJSON_GetStringValue(
            cJSON_GetObjectItemCaseSensitive(server, "country")
        );

        const char *host = cJSON_GetStringValue(
            cJSON_GetObjectItemCaseSensitive(server, "host")
        );

        if (!country || !host)
            continue;

        if (strcmp(country, target_country) == 0) 
        {
            if (add_string(listCountry, sizeCountry, capacityCountry, host) != APP_OK)
                return APP_SEARCH_FAILURE;
        } 
        else 
        {
            if (add_string(list, size, capacity, host) != APP_OK)
                return APP_SEARCH_FAILURE;
        }
    }

    return APP_OK;
}

int find_best_server(char **list, size_t size, size_t *out_index)
{
    if (!list || size == 0 || !out_index)
        return APP_ERROR;

    curl_off_t minTime = LLONG_MAX;
    size_t chosenIndex = 0;
    int found = 0;

    for (size_t i = 0; i < size; ++i) 
    {
        if (!list[i])
            continue;

        struct Response response = {0};
        int result = http_get(list[i], &response, 1);

        if (result != APP_OK)
            continue;

        if (response.us_downloadTime < minTime) 
        {
            minTime = response.us_downloadTime;
            chosenIndex = i;
            found = 1;
        }
    }

    if (!found)
        return APP_SEARCH_FAILURE;

    *out_index = chosenIndex;
    return APP_OK;
}

char* best_server_get(const char* speed_test_file)
{
    FILE* f = data_importer_open_file(speed_test_file);

    if (!f)
        return NULL;

    char* json_string = data_importer_get_buffer(f);

    if (!json_string)
    {
        fclose(f);
        return NULL;
    }

    cJSON *root = cJSON_Parse(json_string);

    data_importer_cleanup(f, json_string);

    if (!root)
    {
        return NULL;
    }

    if (!cJSON_IsArray(root)) 
    {
        cJSON_Delete(root);
        return NULL;
    }

    char** listCountry = NULL;
    size_t sizeCountry = 0;
    size_t capacityCountry = 0;

    char** list = NULL;
    size_t size = 0;
    size_t capacity = 0;

    cJSON *location = NULL;
    if (location_service_get(&location) != APP_OK)
    {
        cJSON_Delete(root);
        return NULL;
    }

    char* countryName = location_service_get_country(location);

    if (countryName == NULL)
    {
        cJSON_Delete(root);
        cJSON_Delete(location);
        return NULL;
    }

    if (split_servers_by_country(root, countryName, 
            &listCountry, &sizeCountry, &capacityCountry,
            &list, &size, &capacity) != APP_OK)
    {
        free_string_list(listCountry, sizeCountry);
        free_string_list(list, size);
        cJSON_Delete(root);
        cJSON_Delete(location);
        return NULL;
    }

    char* best = NULL;
    size_t index = 0;
    if (find_best_server(listCountry, sizeCountry, &index) == APP_OK)
    {
        best = strdup(listCountry[index]);
    }
    else if (find_best_server(list, size, &index) == APP_OK)
    {
        best = strdup(list[index]);
    }
    else
    {
        free_string_list(listCountry, sizeCountry);
        free_string_list(list, size);
        cJSON_Delete(root);
        cJSON_Delete(location);
        return NULL;
    }

    free_string_list(listCountry, sizeCountry);
    free_string_list(list, size);

    cJSON_Delete(location);
    cJSON_Delete(root);

    return best;
}

int best_server_is_alive(const char* url)
{
    struct Response response = {0};
    int result = http_get(url, &response, 1);

    if (result != APP_OK)
        return APP_FAILED_TO_CONN_TO_SERV;

    return APP_OK;
}