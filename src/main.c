    /* 1. Parse cities into city_array
       2. TODO: Get user input and check if in array
       3. TODO: If city in array print URL
       4. TODO: call api with curl
       5. TODO: print output
       4. TODO: return to top
    */


#include "parse.h"
#include <stdio.h>
#include <stdint.h>


int main() {
    City_t city_array[16];
    uint8_t cc = 0; /* City counter */

    
    /* Pass arrays by name; they automatically convert to pointers to their first element.
       The '&' operator is only needed for passing individual variables by reference. */
    parse_city_into_array(city_array, city_list, &cc);
    parse_print_city(city_array, &cc);

    return 0;
    
}
