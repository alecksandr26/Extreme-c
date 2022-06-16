#include <stdio.h>
#include <stdlib.h>

#include "item.h"

struct item_t {
    unsigned char weight;
    struct item_t *next;
};


Item *create_item(const unsigned char weight)
{
    Item *item;
    
    if ((item =(Item *) malloc(sizeof(Item))) == NULL) {
        fprintf(stderr, "Error: There is not enough memory to allocate an Item\n");
        exit(EXIT_FAILURE);
    }

    if (weight > ITEM_MAX_WEIGHT)
        return NULL;

    item->weight = (unsigned char) weight;
    item->next = NULL;
    
    return item;
}


void item_set_next(Item *item, const Item *next)
{
    item->next = (Item *) next;
}


Item *item_get_next(Item *item)
{
    return item->next;
}

const unsigned char item_get_weight(Item *item)
{
    return item->weight;
}


void destroy_item(Item *item)
{
    Item *aux;
    
    while (item != NULL) {
        aux = item;
        item = item->next;
        free(aux);
    }
}

