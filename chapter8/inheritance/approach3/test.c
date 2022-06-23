#include <stdio.h>
#include "animal.h"

int main()
{
    Animal *a;

    a = create_animal("Carlos", 20);

    printf("name: %s\n", animal_get_name(a));

    animal_set_name(a, "Pedrito");
            
    printf("new name: %s\n", animal_get_name(a));

    destroy_animal(a);
    return 0;
}
