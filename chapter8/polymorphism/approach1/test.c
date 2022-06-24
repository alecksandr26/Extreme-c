#include <stdio.h>

#include "animal.h"

int main()
{
    Animal *a;

    a = create_animal("Jonhy");

    animal_sound(a);

    destroy_animal(a);
    return 0;
}

