#include <stdio.h>
#include <stdlib.h>

#define __STUDENT__

#include "student.h"

typedef struct student_t {
    Person *person;

    /* Here we add the new attributes */
    Stage stage;
} Student;


static char *stages_string[NUMBER_OF_STAGES] = {"Elementary", "Middle", "High", "College", "Master", "Php"};


/* create_student: returns a new instace of student if successful else returns null */
Student *create_student(const char name[], const unsigned char age, Stage stage)
{
    Student *s;
    Person *p;

    if ((s = malloc(sizeof(Student))) == NULL)
        return NULL;

    if ((p = create_person(name, age)) == NULL)
        return NULL;

    s->person = p;
    s->stage = stage;

    return s;
}


/* student_say_stage: Prints the current stage that his is doing */
void student_say_stage(Student *student)
{
    printf("I'm doing the %s\n", stages_string[student->stage]);
}


/* destroy_student: deallocate one instance of student */
void destroy_student(Student *student)
{
    free(student->person);
    free(student);
}




