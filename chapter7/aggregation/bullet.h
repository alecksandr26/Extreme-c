#ifndef __BULLET_H__
#define __BULLET_H__

#define DEFAULT_DAMAGE 1

typedef struct bullet_t Bullet;


/* create_bullet: Just creates a new bullet */
Bullet *create_bullet(const unsigned char damage);


/* get_damage: Return teh damages of the bullet */
const unsigned char get_damage(Bullet *bullet);

/* destroy_bullet: To destroy the bullet */
void destroy_bullet(Bullet *bullet);


#endif
