#ifndef PARSE_H
#define PARSE_H
#define URL "https://api.open-meteo.com/v1/forecast?latitude=%.4f&longitude=%.4f&current_weather=true"
#define MAX_CITY_ARRAY 16

typedef struct City_t {
    char   city_url[128];
    char   city_name[64];
    double city_lat;
    double city_lon;  
} City_t;

extern const char* city_list;

void parse_city_into_array(City_t *city_array, const char *city_list, int short *cc);
void parse_print_city(City_t *city_array);


#endif /* PARSE_H */
