// http.c
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include "http.h"
#include "parse.h"

int http_curl(City_t *city_array) {

    CURL *curl = curl_easy_init();
    if (!curl) {
	fprintf(stderr, "Curled returned NULL\n");
	return EXIT_FAILURE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, city_array[1].city_url);
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
