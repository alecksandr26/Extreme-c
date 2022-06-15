
/* Include the header file */
#include "car.h"

#include <stdio.h>
#include <assert.h>

int car_move(Car *car)
{
    assert(car != NULL && "Can't exist a null car");

    if (!car->on || car->gas <= 0)
        return -1;
    
    car->gas--;
    return 0;
}


int car_turn(Car *car)
{
    assert(car != NULL && "Can't exist a null car");
    
    if (!car->on && car->gas == 0)
        return -1;
    
    car->on = !car->on;
    return 0;
}


int car_set_gas(Car *car, unsigned long gas)
{
    assert(car != NULL && "Can't exist a null car");
    
    if (gas > GAS_LIMIT || gas == 0)
        return -1;
    
    car->gas = gas;
    return 0;
}



void car_init(Car *car, enum Colors color, short velocity, unsigned char num_chair)
{
    assert(car != NULL && "Can't exist a null car");
    assert(color <= YELLOW && color >= RED && "Invalid color");
    assert(num_chair == 5 || num_chair == 2 || num_chair == 4 && "Invalid number of chairs");
    
    car->color = color;
    car->gas = 0;
    car->num_chair = num_chair;
    car->velocity = velocity;
}





