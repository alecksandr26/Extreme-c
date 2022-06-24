#ifndef __CAT_H__
#define __CAT_H__

#include "animal.h"

#ifndef __CAT__
#define __CAT__

typedef struct cat_t {
    Animal *animal;
} Cat;

/* cat_get_name: Returns the name of the cat if successful else Returns null */
#define cat_get_name(cat) animal_get_name((cat)->animal)

/* cat_sound: Prints the sound of the animal */
#define cat_sound(cat) animal_sound((cat)->animal)

#else

typedef struct cat_t Cat;

#endif

/* create_cat: Returns a new instace of the class cat if successful else returns NULL */
Cat *create_cat(const char name[]);

/* destroy_cat: Deallocates an instance of a class cat */
void destroy_cat(Cat *cat);

#endif



