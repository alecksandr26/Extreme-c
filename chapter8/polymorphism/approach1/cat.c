#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define __CAT__

#include "cat.h"

struct cat_t {
    Animal *animal;
    char *noise;
};

/* cat_get_name: Returns the name of the cat if successful else Returns null */
#define cat_get_name(cat) animal_get_name((cat)->animal)

/* cat_sound: Prints the sound of the animal */
#define cat_sound(cat) animal_sound((cat)->animal)


static void __cat_sound(Animal *cat)
{
    printf("%s: GRRRRrrrhhhh!!!!\n", animal_get_name(cat));
    
}


/* create_cat: Returns a new instace of the class cat if successful else returns NULL */
Cat *create_cat(const char name[])
{
    Cat *cat;

    if ((cat = malloc(sizeof(Cat))) == NULL)
        return NULL;

    if ((cat->animal = create_animal(name)) == NULL)
        return NULL;

    cat->noise = "GRrrrrr!!!!!";

    /* The magic happens here my friend */
    cat->animal->animal_sound = (void (*)(void *)) &__cat_sound;
    
    return cat;
}

/* destroy_cat: Deallocates an instance of a class cat */
void destroy_cat(Cat *cat)
{
    destroy_animal(cat->animal);
    free(cat);
}


