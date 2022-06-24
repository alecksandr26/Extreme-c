#ifndef __CAT_H__
#define __CAT_H__

#include "animal_p.h"

/* This is my favorite implementation of polymorphic becase we can encapsulate the data that we want
   Change the codebase functions
 */

typedef struct {
    Animal animal; /* Put in the first position the inheritance class */
    char *noise;
} Cat;

/* cat_get_name: Returns the name of the cat if successful else Returns null */
#define cat_get_name(cat) animal_get_name(cat)

/* cat_sound: Prints the sound of the animal */
#define cat_sound(cat) animal_sound(cat)

/* create_cat: Returns a new instace of the class cat if successful else returns NULL */
Cat *create_cat(const char name[]);

/* destroy_cat: Deallocates an instance of a class cat */
void destroy_cat(Cat *cat);

#endif

