#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#define MAX_LENGTH_NAME 50

/* To be able to do polymorphisim  we need to have polymorphic clases and this is a polymorphic
   Something importnat put the public attributes upper and the private attributes downer 
 */
typedef struct {
    
    /* This is going to be the polymorphic function */
    void (*animal_sound)(void *animal);

    /* The private variables must be declared here */
    char name[MAX_LENGTH_NAME];
} Animal;

/* create_animal: Returns a new instance of the class animal if successful else returns null */
Animal *create_animal(const char name[]);

/* animal_get_name: Returns the name of the animal if successful else returns null */
const char *animal_get_name(Animal *animal);

/* animal_sound: Prints the sound of the animal */
void animal_sound(Animal *animal);

/* destroy_animal: Deallocates one instance of animal */
void destroy_animal(Animal *animal);

#endif
