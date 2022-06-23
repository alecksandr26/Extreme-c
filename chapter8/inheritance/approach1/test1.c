#include <stdio.h>

#include "student.h"


int main()
{
    Student *s;

    s = create_student("Pedrito", 21, COLLEGE);

    student_say_name(s);
    student_say_stage(s);
    
    destroy_student(s);
    return 0;
}


