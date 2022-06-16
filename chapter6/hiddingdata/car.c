
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/* Include the header file and also encapsulate and hide the data */
#include "car.h"

struct car_t {
    enum Colors color;
    unsigned char gas;
    unsigned char num_chair;
    short velocity;
    bool on;
};


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


int car_set_gas(Car *car, unsigned char gas)
{
    assert(car != NULL && "Can't exist a null car");
    
    if (gas > GAS_LIMIT || gas == 0)
        return -1;
    
    car->gas = gas;
    return 0;
}


unsigned char car_get_gas(Car *car)
{
    return car->gas;
}


Car *create_car(enum Colors color, short velocity, unsigned char num_chair)
{
    Car *car;
    
    if ((car = (Car *) malloc(sizeof(Car))) == NULL) {
        fprintf(stderr, "Error: There is not enough memory to Car\n");
        exit(EXIT_FAILURE);
    }
    
    assert(car != NULL && "Can't exist a null car");
    assert(color <= YELLOW && color >= RED && "Invalid color");
    assert(num_chair == 5 || num_chair == 2 || num_chair == 4 && "Invalid number of chairs");
    
    car->color = color;
    car->gas = 0;
    car->num_chair = num_chair;
    car->velocity = velocity;

    return car;
}



void destroy_car(Car *car)
{
    free(car);
}





