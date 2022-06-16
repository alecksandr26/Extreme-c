
#include <stdio.h>
#include <assert.h>

#include "gun.h"


int main()
{
    Gun *gun;
    Bullet *bullet;

    gun = create_gun(10, 5, 2);

    assert(gun_get_amount_bullets(gun) == 10 && "Error: It should be there 10 bullets");

    bullet = create_bullet(0);

    gun_insert_bullet(gun, bullet);

    assert(gun_get_amount_bullets(gun) == 11 && "Error: It should be there 11 bullets");

    bullet = gun_shot(gun);

    destroy_bullet(bullet);
    
    assert(gun_get_amount_bullets(gun) == 10 && "Error: It should be there 10 bullets");
    
    destroy_gun(gun);
    
    return 0;
}

