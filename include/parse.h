// parse.h
#ifndef PARSE_H
#define PARSE_H
#define URL "https://api.open-meteo.com/v1/forecast?latitude=%.4f&longitude=%.4f&current=temperature_2m,relative_humidity_2m,wind_speed_10m"
#define MAX_CITY_ARRAY 16

typedef struct parse_json_response_t {
    double temperature;
    double windspeed;
    double rel_humidity;
} parse_json_response_t;

typedef struct parse_city_t {
    char   city_url[256];
    char   city_name[64];
    double city_lat;
    double city_lon;
    parse_json_response_t city_weather;
} parse_city_t;

extern const char* city_list;

void parse_city_into_array(parse_city_t *city_array, const char *city_list);
void parse_print_city(parse_city_t *city_array);
int parse_json_response(parse_city_t *city_array, char **curl_buf, short int *user_choice);


#endif /* PARSE_H */
