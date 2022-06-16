#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gun.h"

struct gun_t {
    unsigned char amount_bullets;
    Bullet *bullets[MAX_AMOUNT_BULLETS];
    unsigned char power;
};


Gun *create_gun(const unsigned char amount_bullets,
                const unsigned char power,
                const unsigned char bullet_damage)
{
    Gun *new_gun;
    int i;
    
    if (amount_bullets > MAX_AMOUNT_BULLETS) 
        return NULL;

    if ((new_gun = (Gun *) malloc(sizeof(Gun))) == NULL) {
        fprintf(stderr, "Error: There is not enough memory for Gun\n");
        exit(EXIT_FAILURE);
    }
        
    new_gun->amount_bullets = amount_bullets;
    
    memset(new_gun->bullets, 0, MAX_AMOUNT_BULLETS);
    for (i = 0; i < amount_bullets; ++i)
        new_gun->bullets[i] = create_bullet(bullet_damage);
    
    return new_gun;
}


Bullet *gun_shot(Gun *gun)
{
    Bullet *bullet;

    if (gun->amount_bullets == 0)
        return NULL;
    
    bullet = gun->bullets[--gun->amount_bullets];
    gun->bullets[gun->amount_bullets] = NULL;

    return bullet;
}


const unsigned char gun_get_amount_bullets(Gun *gun)
{
    return gun->amount_bullets;
}
    


int gun_insert_bullet(Gun *gun, Bullet *bullet)
{
    if (gun->amount_bullets == MAX_AMOUNT_BULLETS)
        return -1;

    gun->bullets[gun->amount_bullets++] = bullet;
    
    return 0;
}


void destroy_gun(Gun *gun)
{
    int i;

    for (i = 0; i < gun->amount_bullets; ++i)
        if (gun->bullets[i] != NULL)
            destroy_bullet(gun->bullets[i]);
    
    free(gun);
}






