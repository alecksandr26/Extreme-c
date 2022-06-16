#ifndef __ITEM_H__
#define __ITEM_H__

#define ITEM_MAX_WEIGHT 100

/* Here Again force the encapsulation */
typedef struct item_t Item;

/* create_item: Creates a new item return NULL if something comes wrong */
Item *create_item(const unsigned char weight);

/* item_set_next: Insert the next element */
void item_set_next(Item *item, const Item *next);

/* item_get_next: Get the next elment */
Item *item_get_next(Item *item);

/* item_get_wegiht: Gets the weight of the item */
const unsigned char item_get_weight(Item *item);

/* destroy_item: Removes all the allocated items */
void destroy_item(Item *item);

#endif
