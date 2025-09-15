// http.c
#include "http.h"
#include "parse.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int http_curl(City_t *city_array, uint8_t *cc) {

    CURL *curl = curl_easy_init();
    if (!curl) {
	fprintf(stderr, "Curled returned NULL\n");
	return EXIT_FAILURE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, city_array[*cc].city_url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
	fprintf(stderr, "Curl performed bad: %s\n", curl_easy_strerror(res));
	curl_easy_cleanup(curl);
	return EXIT_FAILURE;
    }
    
    curl_easy_cleanup(curl);

    return EXIT_SUCCESS;
}
