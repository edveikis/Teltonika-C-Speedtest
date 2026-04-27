#include "httpClient.h"

/// @brief Callback function to store data from request
/// @param data raw data from response
/// @param size size of one element(byte usually)
/// @param element_count number of elements
/// @param user_data ptr passed via CURLOPT_WRITEDATA to store data
/// @return total size
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

/// @brief Callback function to discard data from request
size_t discard_callback(void *data, size_t size, size_t element_count, void *user_data) 
{
    size_t total_size = size * element_count;

    return total_size;
}

int http_get(const char* dst, struct Response* response, int discard)
{
    CURL *curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/8.15.0");
    curl_easy_setopt(curl, CURLOPT_URL, dst);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);

    if (discard == 0)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    else
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discard_callback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK || res == CURLE_OPERATION_TIMEDOUT)
    {
        curl_off_t pretransfer_us = 0, total_us = 0, downloaded = 0;
        curl_easy_getinfo(curl, CURLINFO_PRETRANSFER_TIME_T, &pretransfer_us);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T,       &total_us);
        curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T,    &downloaded);

        double transfer_sec = (total_us - pretransfer_us) / 1e6; // 1*10^6
        response->downloadSize  = downloaded;
        response->downloadSpeed = (curl_off_t)(transfer_sec > 0 ? downloaded / transfer_sec : 0); // Bytes per second
    }
   
    curl_easy_cleanup(curl);

    if (res != CURLE_OK && res != CURLE_OPERATION_TIMEDOUT) 
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

int http_post(const char* dst, struct Response* response, const void* data, size_t size, int discard)
{
    CURL *curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

    // Make post request
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/8.15.0");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)size);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, dst);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);

    if (discard == 0)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    else
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discard_callback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK || res == CURLE_OPERATION_TIMEDOUT)
    {
        curl_off_t pretransfer_us = 0, total_us = 0, uploaded = 0;
        curl_easy_getinfo(curl, CURLINFO_PRETRANSFER_TIME_T, &pretransfer_us);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T,       &total_us);
        curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD_T,      &uploaded);
        curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T,    &response->downloadSize);

        double transfer_sec = (total_us - pretransfer_us) / 1e6; // 1*10^6
        response->uploadSize  = uploaded;
        response->uploadSpeed = (curl_off_t)(transfer_sec > 0 ? uploaded / transfer_sec : 0); // Bytes per second
        response->us_uploadTime = total_us;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK && res != CURLE_OPERATION_TIMEDOUT) 
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