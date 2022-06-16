#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"

struct bullet_t {
    unsigned char damage;
};



Bullet *create_bullet(const unsigned char damage)
{
    Bullet *new_bullet;
    
    if ((new_bullet = (Bullet *) malloc(sizeof(Bullet))) == NULL) {
        fprintf(stderr, "Error: Not enough memory to create a bullet\n");
        exit(EXIT_FAILURE);
    }

    new_bullet->damage = (damage == 0) ? DEFAULT_DAMAGE : damage;

    return new_bullet;
}


const unsigned char get_damage(Bullet *bullet)
{
    return bullet->damage;
}


void destroy_bullet(Bullet *bullet)
{
    free(bullet);
}

