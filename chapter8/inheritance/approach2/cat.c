#include <stdio.h>
#include <stdlib.h>

/* This approach uses a private header files */
#include "cat_p.h"


/* create_cat: Returns a new instace of a cat if successful else return null */
Cat *create_cat(const char name[], const unsigned char age)
{
    Cat *cat;

    if ((cat = malloc(sizeof(Cat))) == NULL
        || (cat->sound = malloc(sizeof(MAX_LENGTH_NAME))) == NULL)
        return NULL;

    cat->sound = "GRrrrrhhhhh!!!!!";

    if ((cat->animal = create_animal(name, age)) == NULL)
        return NULL;

    
    return cat;
}

/* destroy_cat: Deallocates an instance of a cat */
void destroy_cat(Cat *cat)
{
    free(cat->animal);
    free(cat);
}

/* cat_make_noise: Prints the noise that the cat do */
void cat_make_noise(Cat *cat)
{
    printf("Cat %s makes %s\n", cat_get_name(cat), cat->sound);
}



