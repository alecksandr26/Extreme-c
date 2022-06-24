#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#define MAX_LENGTH_NAME 50

#ifndef __ANIMAL__
#define __ANIMAL__

typedef struct {
    /* This is going to be the polymorphic function
       Can be use it as a public attibutes
     */
    
    void (*animal_sound)(void *animal);
} Animal;

#else

typedef struct animal_t Animal;

#endif

/* create_animal: Returns a new instance of the class animal if successful else returns null */
Animal *create_animal(const char name[]);

/* animal_get_name: Returns the name of the animal if successful else returns null */
const char *animal_get_name(Animal *animal);

/* animal_sound: Prints the sound of the animal */
void animal_sound(Animal *animal);

/* destroy_animal: Deallocates one instance of animal */
void destroy_animal(Animal *animal);

#endif
