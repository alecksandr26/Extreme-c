#include <stdio.h>

#include "cat.h"


int main()
{

    Cat *c;

    c = create_cat("Pancho", 20);

    printf("name: %s\n", cat_get_name(c));
    cat_set_name(c, "Julio");
    
    printf("new name: %s\n", cat_get_name(c));

    cat_make_noise(c);
    
    destroy_cat(c);
    return 0;

}


