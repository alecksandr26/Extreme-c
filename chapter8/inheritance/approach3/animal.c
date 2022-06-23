#include <stdlib.h>
#include <string.h>

#include "animal.h"

struct animal_t {
    char name[MAX_LENGTH_NAME];
    unsigned char age;
};


/* create_animal: Returns a new instace of animal if successful else return null */
Animal *create_animal(const char name[], const unsigned char age)
{
    Animal *a;
    
    if (strlen(name) > MAX_LENGTH_NAME)
        return NULL;

    if ((a = (Animal *) malloc(sizeof(Animal))) == NULL)
        return NULL;

    memcpy(a->name, name, MAX_LENGTH_NAME);
    a->age = age;
    
    return a;
}




/* animal_get_name: Returns animal name if successful else return null */
const char *animal_get_name(Animal *animal)
{
    if (animal == NULL)
        return NULL;

    return animal->name;
}

/* animal_set_name: Return 0 if the new name sets perfectly else return -1 */
int animal_set_name(Animal *animal, const char new_name[])
{
    if (strlen(new_name) > MAX_LENGTH_NAME)
        return -1;

    memcpy(animal->name, new_name, MAX_LENGTH_NAME);
    
    return 0;
}



/* destroy_animal: Deallocates an instacne of animal */
void destroy_animal(Animal *animal)
{
    free(animal);
}






