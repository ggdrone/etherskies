// http.h
#ifndef HTTP_H
#define HTTP_H
#include "parse.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct http_membuf_t {
    char* data;
    size_t size;
} http_membuf_t;

size_t http_write_data(void *buffer, size_t size, size_t nmemb, void *userp);
int http_curl(parse_city_t *city_array, short int *user_choice, char **curl_buf, size_t *curl_buf_len);
void http_free_and_clear(char **curl_buf, size_t *curl_buf_len);


#endif
