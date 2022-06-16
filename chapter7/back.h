#ifndef __BACKPACK_H__
#define __BACKPACK_H__

#define MAX_WEIGHT 100

/* Using this method force the encapsulation of the objects */
typedef struct back_t Backpack;

/* create_back: Creates a backpack */
Backpack *create_back();

/* destroy_back: Destroy the backpack deallocates all the dynamic memory */
void destroy_back(Backpack *back);

/* back_set_weight: Sets the weight return "0" if successul else otherwise */
int back_set_weight(Backpack *back, const unsigned char weight);

/* back_push_item: Push an item to the backpack return "0" if successull else otherwise */
int back_push_item(Backpack *back, const unsigned char weight_item);

/* back_pop_item: Removes an item and return the weight of the item */
const unsigned char back_pop_item(Backpack *back);

/* back_get_weight: Gets the weight  */
const unsigned char back_get_weight(Backpack *back);

#endif

