#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

struct person_t {
    char name[MAX_LENGTH_OF_NAME];
    unsigned char age;
};


/* create_person: Return a new instace of a Person if successful else return null */
Person *create_person(const char name[], const unsigned char age)
{
    Person *p;

    if ((p = malloc(sizeof(Person))) == NULL)
        return NULL;

    if (strlen(name) > MAX_LENGTH_OF_NAME || age > 150) {
        free(p);
        return NULL;
    }
    
    memcpy(p->name, name, MAX_LENGTH_OF_NAME);
    p->age = age;

    return p;
}



/* person_say_name: Prints name of a person */
void person_say_name(Person *person)
{
    printf("Hello my name is %s and i have %o\n", person->name, person->age);
}


/* destroy_person: Destroy a an instance of a person */
void destroy_person(Person *person)
{
    free(person);
}


