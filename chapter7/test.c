#include <stdio.h>
#include <assert.h>

#include "back.h"


int main()
{
    Backpack *back;

    back = create_back();

    assert(back_get_weight(back) == MAX_WEIGHT && "Faild: the weight should be MAX_WEIGHT");

    assert(back_push_item(back, 10) == 0 && "Fails: Should to return 1");
    
    destroy_back(back);
    return 0;
}
