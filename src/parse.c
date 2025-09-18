#include "parse.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cities.h"

void parse_city_into_array(City_t *city_array, const char *city_list, uint8_t *cc) {

    /* Keeping track of numbers of chars read
       And our current poisition in the string */
    int chars_read = 0;
    const char *current_pos = city_list; /* Points to the start */
        
    /* Parse out name, lat and lon per city in city_list. %n returns numbers of
       characters read, '\n`and ` ` consumes new lines and spaces  */
    while (sscanf(current_pos, "%[^:]:%lf:%lf\n %n",
		  city_array[*cc].city_name,
		  &city_array[*cc].city_lat,
		  &city_array[*cc].city_lon,
	          &chars_read) == 3) {
	/* Construct URL */
	snprintf(city_array[*cc].city_url,
		 sizeof(city_array[*cc].city_url),
		 URL,
		 city_array[*cc].city_lat,
		 city_array[*cc].city_lon);
	
	/* Increment City Counter (cc) */
	(*cc)++;
	/* Advance pointer to the next line */
	current_pos += chars_read;    
    }
    
}

/* Helper function, print all city names */
void parse_print_city(City_t *city_array, uint8_t *cc) {
    uint8_t i;
    for (i = 0; i < *cc; i++) {
	printf("| %-20s | %s\n", city_array[i].city_name, city_array[i].city_url);

    }
}
