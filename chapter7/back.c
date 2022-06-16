/* This is a code example of how to do composition */
#include <stdio.h>
#include <stdlib.h>

#include "back.h"

/* To relize the composition */
#include "item.h"


/* Force the encapsulation */
struct back_t {
    unsigned char weight;
    unsigned char amount_items;
    Item *head; /* Do composition */
};



int back_set_weight(Backpack *back, const unsigned char weight)
{
    if (MAX_WEIGHT < weight || back->head != NULL)
        return -1;
    
    back->weight = (unsigned char) weight;
    return 0;
}



const unsigned char back_get_weight(Backpack *back)
{
    return back->weight;
}


int back_push_item(Backpack *back, const unsigned char weight_item)
{
    Item *new_item;

    if (weight_item > back->weight)
        return -1;

    new_item = create_item(weight_item);

    if (back->head == NULL)
        back->head = new_item;

    else {
        item_set_next(new_item, back->head);
        back->head = new_item;
    }

    back->amount_items++;

    back->weight -= weight_item;

    return 0;
}


const unsigned char back_pop_item(Backpack *back)
{
    Item *item;
    unsigned char weight;

    item = NULL;
    if (back->amount_items > 0) {
        item = back->head;
        back->head = item_get_next(back->head);
        back->amount_items--;
        weight = item_get_weight(item);
        free(item);
        back->weight += weight;
        return weight;
    }

    return 0;
}



Backpack *create_back()
{
    Backpack *back;
    
    if ((back = (Backpack *) malloc(sizeof(Backpack))) == NULL) {
        fprintf(stderr, "Error: There is not enough memory to allocate object Backpack\n");
        exit(EXIT_FAILURE);
    }
        
    back->amount_items = 0;
    back->head = NULL;
    back->weight = MAX_WEIGHT;
    
    return back;
}


void destroy_back(Backpack *back)
{
    destroy_item(back->head);
    free(back);
}
