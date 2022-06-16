/* This is an example of Aggregation in OOP */
#ifndef __GUN_H__
#define __GUN_H__

#include "bullet.h"

#define MAX_AMOUNT_BULLETS 25

typedef struct gun_t Gun;

/* create_gun: Createsa  gun if there is something gron with it return NULL else return the object Gun */
Gun *create_gun(const unsigned char amount_bullets,
                const unsigned char power,
                const unsigned char bullet_damage);


/* destroy_gun: To destroy all and deallocate all the memory */
void destroy_gun(Gun *gun);


/* gun_shot: Shots a bullet from the gun if there are not bullets in the gun return NULL */
Bullet *gun_shot(Gun *gun);


/* gun_insert_bullet: Insert a bullet to the gun return "0" if successful else otherwise */
int gun_insert_bullet(Gun *gun, Bullet *bullet);

/* gun_get_amount_bullets: Return the amount of bullets of the pistol */
const unsigned char gun_get_amount_bullets(Gun *gun);

#endif

