#include "parse.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

const char* city_list =
    "Stockholm:59.3293:18.0686\n"
    "Göteborg:57.7089:11.9746\n"
    "Malmö:55.6050:13.0038\n"
    "Uppsala:59.8586:17.6389\n"
    "Västerås:59.6099:16.5448\n"
    "Örebro:59.2741:15.2066\n"
    "Linköping:58.4109:15.6216\n"
    "Helsingborg:56.0465:12.6945\n"
    "Jönköping:57.7815:14.1562\n"
    "Norrköping:58.5877:16.1924\n"
    "Lund:55.7047:13.1910\n"
    "Gävle:60.6749:17.1413\n"
    "Sundsvall:62.3908:17.3069\n"
    "Umeå:63.8258:20.2630\n"
    "Luleå:65.5848:22.1567\n"
    "Kiruna:67.8558:20.2253\n";

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
	/* It is wide */
	printf("%-10s\n", city_array[i].city_name);
    }
    
}
