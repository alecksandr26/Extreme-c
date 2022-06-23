#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#define MAX_LENGTH_NAME 50


typedef struct animal_t Animal;

/* create_animal: Returns a new instace of animal if successful else return null */
Animal *create_animal(const char name[], const unsigned char age);

/* animal_get_name: Returns animal name if successful else return null */
const char *animal_get_name(Animal *animal);

/* animal_set_name: Return 0 if the new name sets perfectly else return -1 */
int animal_set_name(Animal *animal, const char new_name[]);

/* destroy_animal: Deallocates an instacne of animal */
void destroy_animal(Animal *animal);


#endif





