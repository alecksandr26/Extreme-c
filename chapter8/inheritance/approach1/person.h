#ifndef __PERSON_H__
#define __PERSON_H__

#define MAX_LENGTH_OF_NAME 50

/* Encapsulates the object person */
typedef struct person_t Person;

/* create_person: Return a new instace of a Person if successful else return null */
Person *create_person(const char name[], const unsigned char age);

/* person_say_name: Prints name of a person */
void person_say_name(Person *person);

/* destroy_person: Destroy a an instance of a person */
void destroy_person(Person *person);


#endif

