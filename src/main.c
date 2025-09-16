/*
   1. x: Parse cities into city_array
   2. x: Get user input and check if in array
   3. x: If city in array print URL
   4. x: call api with curl
   5. x: print output
   6. x: return to top or quit
   7. TODO save respons to buffer
   8. TODO parse respons with jansson?
*/

#include "parse.h"
#include "http.h"
#include "user.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    
    City_t city_array[16];
    /* City counter */
    /* Improvements, let cc be set by user_get_input */
    int short cc = 0; 

    parse_city_into_array(city_array, city_list, &cc);
    	
    while (1) {
	
	parse_print_city(city_array);
	printf("Please select a city from the list (`q` to quit): ");
	cc = user_get_input(city_array);
	/* Setting cc to 0 if city not found in list, send user to top */ 
	if (cc == -1 || cc >= 16) {
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
