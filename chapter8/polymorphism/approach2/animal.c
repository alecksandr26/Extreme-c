#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animal_p.h"

/* These are the private methods which are defual by the clas */

static void animal_default_sound(Animal *animal)
{
    printf("%s: Animal making default sound\n", animal->name);
}


/* create_animal: Returns a new instance of the class animal if successful else returns null */
Animal *create_animal(const char name[])
{
    Animal *a;
    
    if (strlen(name) > MAX_LENGTH_NAME)
        return NULL;

    if ((a = malloc(sizeof(Animal))) == NULL)
        return NULL;

    strcpy(a->name, name);

    /* Casting the function */
    a->animal_sound = (void (*)(void *)) &animal_default_sound;

    return a;
}


/* animal_get_name: Returns the name of the animal if successful else returns null */
const char *animal_get_name(Animal *animal)
{
    if (animal == NULL)
        return NULL;
    
    return animal->name;
}

/* animal_sound: Prints the sound of the animal */
void animal_sound(Animal *animal)
{
    if (animal == NULL)
        return;

    animal->animal_sound((void *) animal);
}

/* destroy_animal: Deallocates one instance of animal */
void destroy_animal(Animal *animal)
{
    free(animal);
}

