#ifndef __CAR_H_
#define __CAR_H_

#include <stdbool.h>

#define GAS_LIMIT 100

enum Colors {
    RED,
    GREEN,
    BLUE,
    YELLOW
};


typedef struct car_t Car;

/* car_move: Moves the car return "0" If okay otherwise return -1 */
int car_move(Car *car);
   
/* car_set_gas: Put gas to the car there is a limit of gas that you could put */
int car_set_gas(Car *car, unsigned char gas);

/* car_get_gas: Gets the gas of the car */
unsigned char car_get_gas(Car *car);

/* car_turn: Turns the car return "0" if successful return otherwise if there is an error */
int car_turn(Car *car);

/* create_car: Createas a new car */
Car *create_car(enum Colors color, short velocity, unsigned char num_chair);

/* car_destroy: Destroy the data of the object */
void destroy_car(Car *car);

#endif
