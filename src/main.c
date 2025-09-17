/* 1. Parsing the JSON
   4. TODO: PARSE THE JSON TO MAKE IT LOOK SMASK
*/

#include "http.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  City_t city_array[MAX_CITY_ARRAY];
  if (parse_city_into_array(city_array, city_list) != 0){
    printf("Failed to parse city string");
    return EXIT_FAILURE;
  }

  char input[32];

  while (1) {
    printf("Choose a city\ntype q to quit\n");
    parse_print_city(city_array);

    if (scanf("%31s", input) != 1) {
      printf("scanf epicfail\n");
      continue;
    }

    if (strcmp(input, "q") == 0) {
      break;
    }

    if (!is_number(input)) {
      printf("Invalid input\n");
      continue;
    }

    int user_choice = atoi(input);
    if (user_choice >= MAX_CITY_ARRAY || user_choice < 0) {
      printf("Invalid choice. Try again\n");
      continue;
    }

    http_curl(city_array, user_choice);
  }

  return 0;
}
