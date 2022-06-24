#include <stdio.h>

#include "cat.h"
#include "duck.h"


int main()
{
    Cat *c;
    Duck *d;

    c = create_cat("julio");
    d = create_duck("Pedrito");
    
    printf("name: %s\n", cat_get_name(c));
    printf("name: %s\n", cat_get_name(d));

    cat_sound(c);
    duck_sound(d);

    /* Look this is polymorphic We are using the original code base of aninmal
       And we are overwriting it
     */

    animal_sound((Animal *) c);
    animal_sound((Animal *) d);

    destroy_duck(d);
    destroy_cat(c);
    
    return 0;
}

