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
   8. x: parse respons with janssonp
   9. TDDO save parsed data to file
  10. TODO if data to old do not load
  11. ?? 
*/

#include "parse.h"
#include "http.h"
#include "user.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    
    parse_city_t city_array[16];
    char *curl_buf = NULL;
    size_t curl_buf_len = 0;
    short int user_choice = 0;

    parse_city_into_array(city_array, city_list);
    	
    while (1) {
	
	parse_print_city(city_array);
	printf("Please select a city from the list (`q` to quit): ");

	user_choice = user_get_input(city_array);
	if (user_choice == -1 || user_choice >= 16) {
	    continue;
	} 

	printf("City selected: %s\n", city_array[user_choice].city_name);
	http_curl(city_array, &user_choice, &curl_buf, &curl_buf_len);
	if (curl_buf && curl_buf_len > 0) {
	    printf("\tCURL data saved!\n");
	    printf("\tLength of data: %zu bytes\n\n", curl_buf_len);

	}

	parse_json_response(city_array, &curl_buf, &user_choice);
	printf("\tCurrent weather in: %s\n", city_array[user_choice].city_name);
	printf("\tTemperature: %.1lf C\n", city_array[user_choice].city_weather.temperature);
	printf("\tWindspeed: %.1lf km/s\n", city_array[user_choice].city_weather.windspeed);
	printf("\tRelative humidity: %.1lf%%\n\n", city_array[user_choice].city_weather.rel_humidity);

	http_free_and_clear(&curl_buf, &curl_buf_len)
	
    }

    return EXIT_SUCCESS;
    
}
