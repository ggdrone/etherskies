// main.c
/*
   1. x: Parse cities into city_array
   2. x: Get user input and check if in array
   3. x: If city in array print URL
   4. x: call api with curl
   5. x: print output
   6. x: return to top or quit
   7. X: save curl respons and length to buffer, and passed into main (see .md file for explanation)
 7/8. TODO helperfunction for free(curl_buf) and resetting buf and buf_len
   8. TODO parse respons with janssonp
   9. TDDO save parsed data to file
  10. TODO if data to old do not load
  11. TODO 
*/

#include "parse.h"
#include "http.h"
#include "user.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    
    parse_city_t city_array[16];
    char *curl_buf = NULL; /* http_curl() allocates memory dynamically with realloc() */
    size_t curl_buf_len = 0; /* only need a single size_t. */
    short int cc = 0; 

    parse_city_into_array(city_array, city_list, &cc);
    	
    while (1) {
	
	parse_print_city(city_array);
	printf("Please select a city from the list (`q` to quit): ");
	cc = user_get_input(city_array);
	if (cc == -1 || cc >= 16) {
	    continue;
	} 
	printf("City selected: %s\n", city_array[cc].city_name);
	printf("City URL: %s\n", city_array[cc].city_url);    
	printf("API respons: \n\n");
	http_curl(city_array, &cc, &curl_buf, &curl_buf_len);
	/* Helper for this? */
	if (curl_buf && curl_buf_len > 0) {
	    printf("CURL data saved!\n");
	    printf("Length of data %zu\n", curl_buf_len);
	    printf("Data:\n");
	    printf("%s", curl_buf);
	    free(curl_buf);
	    curl_buf = NULL;
	    curl_buf_len = 0;
	    
	}
	/* parse_json() */
	printf("\n\n");
	
    }
    
    return EXIT_SUCCESS;
    
}
