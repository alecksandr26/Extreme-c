#ifndef __INTEGER_COUNTER_H__
#define __INTEGER_COUNTER_H__

#include <stdint.h>

struct shared_int32_t;

/* shared_int32_new: Creates a new instance of shared memory of a counter */
struct shared_int32_t* shared_int32_new();

/* shared_int32_delete: Deletes an instace of counter */
void shared_int32_delete(struct shared_int32_t* obj);

/* shared_int32_ctor: The constructor of this object */
void shared_int32_ctor(struct shared_int32_t* obj, const char* name);

/* shared_int32_dtor: The constructor for this counter */
void shared_int32_dtor(struct shared_int32_t* obj);

/* shared_int32_setvalue: Simple setter for this instance */
void shared_int32_setvalue(struct shared_int32_t* obj, int32_t value);

/* shared_int32_setvalue_ifowner: Simple setter if you are the owner of the object */
void shared_int32_setvalue_ifowner(struct shared_int32_t* obj, int32_t value);

/* shared_int32_getvalue: Gets the 32 value */
int32_t shared_int32_getvalue(struct shared_int32_t* obj);


#endif



