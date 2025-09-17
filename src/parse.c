// parse.c
#include "parse.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <jansson.h>

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

void parse_city_into_array(parse_city_t *city_array, const char *city_list) {

    uint8_t i = 0;
    /* Keeping track of numbers of chars read
       And our current poisition in the string */
    int chars_read = 0;
    const char *current_pos = city_list; /* Points to the start */
        
    /* Parse out name, lat and lon per city in city_list. %n returns numbers of
       characters read, '\n`and ` ` consumes new lines and spaces  */
    while (sscanf(current_pos, "%[^:]:%lf:%lf\n %n",
		  city_array[i].city_name,
		  &city_array[i].city_lat,
		  &city_array[i].city_lon,
	          &chars_read) == 3) {
	/* Construct URL */
	snprintf(city_array[i].city_url,
		 sizeof(city_array[i].city_url),
		 URL,
		 city_array[i].city_lat,
		 city_array[i].city_lon);
	
	/* Increment City Counter (cc) */
	i++;
	/* Advance pointer to the next line */
	current_pos += chars_read;    
    }
    
}

/* Helper function, print all city names */
void parse_print_city(parse_city_t *city_array) {

    uint8_t i;
    for (i = 0; i < MAX_CITY_ARRAY; i++) {
	/* It is wide */
	printf(" | %-15s |\n", city_array[i].city_name);
    }
    
}

int parse_json_response(parse_city_t *city_array, char **curl_buf, short int *user_choice) {
    json_error_t error;
    json_t *root = json_loads(*curl_buf, 0, &error);

    if (!root) {
        fprintf(stderr, "JSON error at line %d: %s\n", error.line, error.text);
        return -1;
    }

    json_t *current_weather = json_object_get(root, "current");
    if (!json_is_object(current_weather)) {
        json_decref(root);
        return -1;
    }

    json_t *temperature = json_object_get(current_weather, "temperature_2m");
    json_t *windspeed   = json_object_get(current_weather, "wind_speed_10m");
    json_t *rel_humidity= json_object_get(current_weather, "relative_humidity_2m");

    if (json_is_number(temperature)) city_array[*user_choice].city_weather.temperature = json_number_value(temperature);
    if (json_is_number(windspeed)) city_array[*user_choice].city_weather.windspeed = json_number_value(windspeed);
    if (json_is_number(rel_humidity)) city_array[*user_choice].city_weather.rel_humidity = json_number_value(rel_humidity);

    json_decref(root);
    return 0;
}
