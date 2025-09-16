 // http.c
#include "http.h"
#include "parse.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
  This function is called by CURL whenever a chunk of data is received.
  - contents: pointer to the raw bytes for this chunk (temporary, must copy).
  - size * nmemb: total number of bytes in this chunk.
  - userp: pointer we gave to CURL (our http_membuf_t), 
           where we accumulate the entire HTTP response.
 
  We grow the buffer with realloc, copy the new data to the end,
  and keep building the full response. CURL calls this repeatedly
  until the entire response has been downloaded.
*/
/* function params decided by CURÖ */
size_t http_write_data(void *buffer, size_t size, size_t nmemb, void *userp) { 
    /* Call back function */
    size_t bytes = size * nmemb; 
    printf("Recived chunk: %zu bytes\n", bytes);

    /* We grow the buffer with this size! */
    struct http_membuf_t* mem_t = userp;
    /* Grow buffer with recived chunk
       make room for nullterminator too! */ 
    char *ptr = realloc(mem_t->data, mem_t->size + bytes + 1);
    if (!ptr) {
	printf("Returned 0 to CURL!\n");
	return 0;
    }
    mem_t->data = ptr;
    /* Copies the new data into the buffer
       Data points to the start off the buffer
       size says how many bytes already exists
       New contents gets added to the end off buffer
    */
    memcpy(&(mem_t->data[mem_t->size]), buffer, bytes);
    mem_t->size += bytes;
    mem_t->data[mem_t->size] = '\0'; /* nullterminator */
    return bytes;    
}

int http_curl(parse_city_t *city_array, short int *cc, char **curl_buf, size_t *curl_buf_len) {

    CURL *curl = curl_easy_init();
    if (!curl) {
	fprintf(stderr, "Curled returned NULL\n");
	return EXIT_FAILURE;
    }

    struct http_membuf_t chunk = {0};

    curl_easy_setopt(curl, CURLOPT_URL, city_array[*cc].city_url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_data); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk); /* This is chunk in http_write_data */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* Follow redirects */

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
	fprintf(stderr, "Curl performed bad: %s\n", curl_easy_strerror(res));
	curl_easy_cleanup(curl);
	return EXIT_FAILURE;
    }
    
    curl_easy_cleanup(curl);
    /* Reset City Counter in main */
    *cc = 16;

    /* Return buffer of recived data and size of buffer */
    *curl_buf = chunk.data;
    *curl_buf_len = chunk.size;
    return EXIT_SUCCESS;
}
