# Example of encapsulation
This is an example of how we can encapsulate objects in c and create an instance of that object, to create a real encapsulation we need to matain the attributes hide.
# Encapsulation
Encapsulation simply means putting related things together into a capsule that represents an object. It happens first in your mind, and then it should be transferred to the code. The moment that you feel an object needs to have some attributes and functionalities, you are doing encapsulation in your mind; that encapsulation then needs to be transferred to the code level.
# Hidding data in C
To hide the data creating private variables is easy we only need to define the struct data type like this.<br />
```
typedef struct car_t Car;
```
And inside of the source file define the structure like this.
```
/* Include the header file and also encapsulate and hide the data */
#include "car.h"

struct car_t {
    enum Colors color;
    unsigned char gas;
    unsigned char num_chair;
    short velocity;
    bool on;
};
```
