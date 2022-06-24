#include <stdio.h>
#include "cat.h"


int main()
{
    Cat *c;

    c = create_cat("julio");
    
    printf("name: %s\n", cat_get_name(c));
    
    /* This is one of the problems that I can origin
       This is why I don't like this implementation
     */
    c->animal->animal_sound = NULL;

    cat_sound(c);
    
    destroy_cat(c);
    
    return 0;
}

