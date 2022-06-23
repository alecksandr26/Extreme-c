#ifndef __STUDENT_H__
#define __STUDENT_H__

/* This is the first approach of how to do inheritance in c
   this approach works using a little bit of composition  
 */

#include "person.h"

#define NUMBER_OF_STAGES 6

typedef enum {
    ELEMENTARY,
    MIDDLE,
    HIGH,
    COLLEGE,
    MASTER,
    PHP
} Stage;


/* Defining that is an inheritance maintating the encapsulation and hidding data */
#ifndef __STUDENT__
#define __STUDENT__

typedef struct {
    Person *person;
} Student;

/* student_say_name: Prints student name  */
#define student_say_name(student) person_say_name((student)->person)

#else

typedef struct student_t Student;

#endif


/* create_student: returns a new instace of student if successful else returns null */
Student *create_student(const char name[], const unsigned char age, Stage stage);

/* student_say_stage: Prints the current stage that his is doing */
void student_say_stage(Student *student);

/* destroy_student: deallocate one instance of student */
void destroy_student(Student *student);


#endif
