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


typedef struct {
    enum Colors color;
    unsigned char gas;
    unsigned char num_chair;
    short velocity;
    bool on;
} Car;

/* car_move: Moves the car return "0" If okay otherwise return -1 */
int car_move(Car *car);
   
/* car_set_gas: Put gas to the car there is a limit of gas that you could put */
int car_set_gas(Car *car, unsigned char gas);

/* car_get_gas: Gets the gas of the car */
#define car_get_gas(car) ((car)->gas)

/* car_turn: Turns the car return "0" if successful return otherwise if there is an error */
int car_turn(Car *car);

/* car_init: Initialize a car */
void car_init(Car *car, enum Colors color, short velocity, unsigned char num_chair);

/* car_destroy: Destroy the data of the object */
void car_destroy(Car *car);

#endif


 
