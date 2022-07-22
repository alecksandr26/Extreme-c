#ifndef __MY_SHARED_MEMORY__
#define __MY_SHARED_MEMORY__

#include <stdint.h>

struct shared_mem_t;

typedef int32_t bool_t;

/* shared_mem_new: Create a new instance of the memory */
struct shared_mem_t *shared_mem_new();

/* shared_mem_delete: To delete the shared memory */
void shared_mem_delete(struct shared_mem_t* obj);

/* shared_mem_ctor: Contruct all the memory */
void shared_mem_ctor(struct shared_mem_t* obj, const char* name, size_t size);

/* shared_mem_dtor: deconsturct an instance of the memory */
void shared_mem_dtor(struct shared_mem_t* obj);

/* shared_mem_getptr: Gets the pointer of the shared memory  */
char* shared_mem_getptr(struct shared_mem_t* obj);

/* shared_mem_isowner: To know if we are the owner of the shared memory */
bool_t shared_mem_isowner(struct shared_mem_t* obj);

/* shared_mem_setowner: To set that shared memory to this new process */
void shared_mem_setowner(struct shared_mem_t* obj, bool_t is_owner);


#endif




