#ifndef __CAT_H__
#define __CAT_H__

#include "animal.h"

typedef struct cat_t Cat;

/* cat_get_name: Returns the name of the cat if successful else Returns null */
#define cat_get_name(cat) animal_get_name((Animal *) cat)

/* cat_sound: Prints the sound of the animal */
#define cat_sound(cat) animal_sound((Animal *) cat)

/* create_cat: Returns a new instace of the class cat if successful else returns NULL */
Cat *create_cat(const char name[]);

/* destroy_cat: Deallocates an instance of a class cat */
void destroy_cat(Cat *cat);

#endif



