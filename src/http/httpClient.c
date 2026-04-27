#include "httpClient.h"

/// @brief Callback function to store data from request
/// @param data raw data from response
/// @param size size of one element(byte usually)
/// @param element_count number of elements
/// @param user_data ptr passed via CURLOPT_WRITEDATA to store data
/// @return 
size_t write_callback(void *data, size_t size, size_t element_count, void *user_data) 
{
    size_t total_size = size * element_count;
    struct Response *mem = (struct Response *)user_data;

    char *ptr = realloc(mem->data, mem->size + total_size + 1);

    if (!ptr) 
        return 0;

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), data, total_size);
    mem->size += total_size;
    mem->data[mem->size] = '\0';

    return total_size;
}

int http_make_request(const char* dst, struct Response* response)
{
    CURL *curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    curl_easy_setopt(curl, CURLOPT_URL, dst);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (res != CURLE_OK) 
    {
        fprintf(stderr, "Request failed: %s\n",
            curl_easy_strerror(res));
        free(response->data);
        response->data = NULL;
        response->size = 0;
        return APP_REQUEST_FAILED;
    }

    return CURLE_OK;
}