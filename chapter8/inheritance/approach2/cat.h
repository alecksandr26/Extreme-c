#ifndef __CAT_H__
#define __CAT_H__

#include "animal.h"

/* This approach for my is better because we mantain our code more clean and secure
   making private headers files
 */

typedef struct {
    Animal *animal;
} Cat;

/* create_cat: Returns a new instace of a cat if successful else return null */
Cat *create_cat(const char name[], const unsigned char age);

/* destroy_cat: Deallocates an instance of a cat */
void destroy_cat(Cat *cat);

/* cat_get_name: Returns the name of the cat if successful else return null */
#define cat_get_name(cat) animal_get_name((cat)->animal)

/* cat_set_name: Return 0 if the new name is perfectly seted else return -1 */
#define cat_set_name(cat, name) animal_set_name((cat)->animal, name)

/* cat_make_noise: Prints the noise that the cat do */
void cat_make_noise(Cat *cat);


#endif
