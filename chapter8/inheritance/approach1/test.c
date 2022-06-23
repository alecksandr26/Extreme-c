#include <stdio.h>
#include "./person.h"


int main()
{

    Person *p;

    p = create_person("Pedrito", 20);

    person_say_name(p);

    destroy_person(p);
    
    return 0;
}



