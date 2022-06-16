#include <stdio.h>

#include "car.h"


int main()
{
    Car *car;

    car = create_car(RED, 250, 4);
    
    car_set_gas(car, 10);
    
    if (car_turn(car) == 0)
        printf("Car on | gas = %u\n", car_get_gas(car));
    else
        printf("Car off | gas = %u\n", car_get_gas(car));

    if (car_move(car) == 0)
        puts("Car moving");
    else
        puts("Car not moving");

    destroy_car(car);
            
    return 0;
}


