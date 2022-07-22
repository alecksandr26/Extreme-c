#ifndef __SHARED_MUTEX_P_H__
#define __SHARED_MUTEX_P_H__

/* include the shared memory */
#include "./shared_memory_p.h"

struct shared_mutex_t {
    struct shared_mem_t* shm;
    pthread_mutex_t* ptr;
};

/* shared_mutex_new: Creates a new instance of shared mutex */
struct shared_mutex_t *shared_mutex_new();

/* shared_mutex_delete: Delete the instance of shared memory */
void shared_mutex_delete(struct shared_mutex_t* obj);

/* shared_mutex_ctor: Constructor of shared memory */
void shared_mutex_ctor(struct shared_mutex_t* obj, const char* name);

/* shared_mutex_dtor: Deconstructor of shared memory */
void shared_mutex_dtor(struct shared_mutex_t* obj);

/* shared_mutex_getptr: Get the pointer of the shared memory */
pthread_mutex_t *shared_mutex_getptr(struct shared_mutex_t* obj);

/* shared_mutex_lock: To lock the mutex */
void shared_mutex_lock(struct shared_mutex_t* obj);

/* shared_mutex_unlock: To unlock the mutex */
void shared_mutex_unlock(struct shared_mutex_t* obj);

#if !defined(__APPLE__)
/* shared_mutex_make_consistent: Make consistent the shared mutex */
void shared_mutex_make_consistent(struct shared_mutex_t* obj);
#endif

#endif
