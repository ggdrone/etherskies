#include "user.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Gets user input and tries to find input in city_array.
   Function effectivly increments cc to correct value for
   user input */
int user_get_input(City_t *city_array) {

    char buf[32];
    uint8_t i;

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
	fprintf(stderr, "fgets returned NULL\n");
	return EXIT_FAILURE;
    } else {
	buf[strcspn(buf, "\n")] = '\0';

    }
    
    if (strcmp(buf, "q") == 0) {
	exit(EXIT_SUCCESS);
    }

    /* Hardcoded size of city_array here,
       not great for future */
    for (i = 0; i < MAX_CITY_ARRAY; i++) {
	if (strcmp(buf, city_array[i].city_name) == 0) {
	    /* This is element that contains
	       the users city in city_array */
	    return i;
	}

    }
    
    printf("No such city in database!\n");
    return -1;
}
