    /* 1. Parse cities into city_array
       2. Get user input and check if in array
       3. If city in array print URL
       4. call api with curl
       5. print output
       4. TODO: return to top
    */

#include "parse.h"
#include "http.h"
#include "user.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    City_t city_array[16];
    uint8_t cc = 0; /* City counter */
    
    /* Pass arrays by name; they automatically convert to pointers to their first element.
       The '&' operator is only needed for passing individual variables by reference. */

    parse_city_into_array(city_array, city_list, &cc);
    
	
    while (1) {
	
	parse_print_city(city_array, &cc);
	printf("Please select a city from the list (`q` to quit): ");
	user_get_input(city_array, &cc);
	/* Setting cc to 0 if city not found in list, send user to top */ 
	if (cc == 0) {
	    continue;
	}
	printf("City selected: %s\n", city_array[cc].city_name);
	printf("City URL: %s\n", city_array[cc].city_url);
    
	printf("API respons: \n\n");
	http_curl(city_array, &cc);
	printf("\n\n");
    }
    
    return EXIT_SUCCESS;
    
}
