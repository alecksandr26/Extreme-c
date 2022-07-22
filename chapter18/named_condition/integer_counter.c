#include <stdlib.h>
#include <stdint.h>

/* Include the private header of the counter object */
#include "./integer_counter_p.h"

/* shared_int32_new: Creates a new instance of shared memory of a counter */
struct shared_int32_t *shared_int32_new()
{
    struct shared_int32_t* obj;
    
    obj = (struct shared_int32_t *) malloc(sizeof(struct shared_int32_t));
    obj->shm = shared_mem_new();
    return obj;
}

/* shared_int32_delete: Deletes an instace of counter */
void shared_int32_delete(struct shared_int32_t* obj)
{
    shared_mem_delete(obj->shm);
    free(obj);
}

/* shared_int32_ctor: The constructor of this object */
void shared_int32_ctor(struct shared_int32_t* obj, const char* name)
{
    shared_mem_ctor(obj->shm, name, sizeof(int32_t));
    obj->ptr = (int32_t *) shared_mem_getptr(obj->shm);
}

/* shared_int32_dtor: The constructor for this counter */
void shared_int32_dtor(struct shared_int32_t* obj)
{
    shared_mem_dtor(obj->shm);
}

/* shared_int32_setvalue: Simple setter for this instance */
void shared_int32_setvalue(struct shared_int32_t* obj, int32_t value)
{
    *(obj->ptr) = value;
}

/* shared_int32_setvalue_ifowner: Simple setter if you are the owner of the object */
void shared_int32_setvalue_ifowner(struct shared_int32_t* obj, int32_t value)
{
    if (shared_mem_isowner(obj->shm)) {
        *(obj->ptr) = value;
    }
}

/* shared_int32_getvalue: Gets the 32 value */
int32_t shared_int32_getvalue(struct shared_int32_t* obj)
{
    return *(obj->ptr);
}

