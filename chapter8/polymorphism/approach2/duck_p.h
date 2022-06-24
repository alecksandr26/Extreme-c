#ifndef __DUCK_H__
#define __DUCK_H__

#include "animal_p.h"

typedef struct {
    Animal animal;
    char *noise;
} Duck;

/* duck_get_name: Return the ducks name if successful else returns null */
#define duck_get_name(duck) animal_get_name((Animal *) duck)

/* duck_sound: Prints the duck sound */
#define duck_sound(duck) animal_sound((Animal *) duck)

/* create_duck: Returns a new instace of duck if successful else returns null */
Duck *create_duck(const char name[]);

/* destroy_duck: Deallocates an instace of duck */
void destroy_duck(Duck *duck);

#endif
