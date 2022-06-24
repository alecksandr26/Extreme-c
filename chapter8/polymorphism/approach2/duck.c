#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "duck_p.h"

/* Here I'm Overwriting the method */
static void __duck_noise(Animal *duck)
{
    printf("%s: Quack!!!!\n", duck->name);
}


/* create_duck: Returns a new instace of duck if successful else returns null */
Duck *create_duck(const char name[])
{
    Duck *d;

    if ((d = malloc(sizeof(Duck))) == NULL)
        return NULL;

    if (strlen(name) > MAX_LENGTH_NAME)
        return NULL;


    strcpy(((Animal *) d)->name, name);

    /* make the magic casting */
    ((Animal *) d)->animal_sound = (void (*)(void *))  &__duck_noise;
    
    return d;
}

/* destroy_duck: Deallocates an instace of duck */
void destroy_duck(Duck *duck)
{
    free(duck);
}




