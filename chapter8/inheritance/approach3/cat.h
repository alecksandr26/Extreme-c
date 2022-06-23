#ifndef __CAT_H__
#define __CAT_H__

/* This approach approuch doens't like me too much but can be used whits works with full composition
 */

typedef struct cat_t Cat;

/* create_cat: Returns a new instace of a cat if successful else return null */
Cat *create_cat(const char name[], const unsigned char age);

/* destroy_cat: Deallocates an instance of a cat */
void destroy_cat(Cat *cat);

/* cat_get_name: Returns the name of the cat if successful else return null */
const char *cat_get_name(Cat *cat);

/* cat_set_name: Return 0 if the new name is perfectly seted else return -1 */
int cat_set_name(Cat *cat, const char name[]);

/* cat_make_noise: Prints the noise that the cat do */
void cat_make_noise(Cat *cat);


#endif
