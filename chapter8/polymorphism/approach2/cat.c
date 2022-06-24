#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cat_p.h"

/* Here we are rewrite the method of the default animal */
static void __cat_sound(Cat *cat)
{
    printf("%s: GRRRRrrrhhhh!!!!\n", cat_get_name((Animal *) cat));
}

/* create_cat: Returns a new instace of the class cat if successful else returns NULL */
Cat *create_cat(const char name[])
{
    Cat *cat;
    Animal *a;

    if ((cat = malloc(sizeof(Cat))) == NULL)
        return NULL;

    if (strlen(name) > MAX_LENGTH_NAME)
        return NULL;

    /* Doing pure casting we can insert the name of the animal */
    strcpy(((Animal *) cat)->name, name);
    
    cat->noise = "GRrrrrr!!!!!";

    /* The magic happens here my friend */
    ((Animal *) cat)->animal_sound = (void (*)(void *)) &__cat_sound;
    
    return cat;
}

/* destroy_cat: Deallocates an instance of a class cat */
void destroy_cat(Cat *cat)
{
    free(cat);
}


