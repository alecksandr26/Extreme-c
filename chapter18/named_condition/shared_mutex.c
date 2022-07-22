#include <stdio.h>

/* For alloc memory */
#include <stdlib.h>

/* For errors */
#include <string.h>
#include <errno.h>

/* For pthread */
#include <pthread.h>

#include "./shared_mutex_p.h"

/* shared_int32_new: Creates a new instance of shared memory of a counter */
struct shared_mutex_t *shared_mutex_new()
{
    struct shared_mutex_t* obj;
    obj = (struct shared_mutex_t *) malloc(sizeof(struct shared_mutex_t));
    obj->shm = shared_mem_new();
    return obj;
}
/* shared_mutex_delete: Delete the instance of shared memory */
void shared_mutex_delete(struct shared_mutex_t* obj)
{
    shared_mem_delete(obj->shm);
    free(obj);
}

/* shared_mutex_ctor: Constructor of shared memory */
void shared_mutex_ctor(struct shared_mutex_t* obj, const char* name)
{
    pthread_mutexattr_t mutex_attr;
    int ret;
    
    shared_mem_ctor(obj->shm, name, sizeof(pthread_mutex_t));
    obj->ptr = (pthread_mutex_t*)shared_mem_getptr(obj->shm);
    if (shared_mem_isowner(obj->shm)) {
        if ((ret = pthread_mutexattr_init(&mutex_attr))) {
            fprintf(stderr, "ERROR(%s): Initializing mutex attrs failed: %s\n", name, strerror(ret));
            exit(1);
        }
#if !defined(__APPLE__)
        if ((ret = pthread_mutexattr_setrobust(&mutex_attr, PTHREAD_MUTEX_ROBUST))) {
            fprintf(stderr, "ERROR(%s): Setting the mutex as robust failed: %s\n", name, strerror(ret));
            exit(1);
        }
#endif
        if ((ret = pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED))) {
            fprintf(stderr, "ERROR(%s): Failed to set as process-shared: %s\n", name, strerror(ret));
            exit(1);
        }
        if ((ret = pthread_mutex_init(obj->ptr, &mutex_attr))) {
            fprintf(stderr, "ERROR(%s): Initializing the mutex failed: %s\n", name, strerror(ret));
            exit(1);
        }
        if ((ret = pthread_mutexattr_destroy(&mutex_attr))) {
            fprintf(stderr, "ERROR(%s): Destruction of mutex attrs failed: %s\n", name, strerror(ret));
            exit(1);
        }
    }
}

/* shared_mutex_dtor: Deconstructor of shared memory */
void shared_mutex_dtor(struct shared_mutex_t* obj)
{
    int ret;
    
    if (shared_mem_isowner(obj->shm))
        if ((ret = pthread_mutex_destroy(obj->ptr)))
            fprintf(stderr, "WARN: Destruction of the mutex failed: %s\n", strerror(ret));
    
    shared_mem_dtor(obj->shm);
}

/* shared_mutex_getptr: Get the pointer of the shared memory */
pthread_mutex_t *shared_mutex_getptr(struct shared_mutex_t* obj)
{
    return obj->ptr;
}

/* shared_mutex_lock: To lock the mutex */
void shared_mutex_lock(struct shared_mutex_t* obj)
{
    int ret;

    if ((ret = pthread_mutex_lock(obj->ptr))) {
#if !defined(__APPLE__)
        if (ret == EOWNERDEAD) {
            fprintf(stderr, "WARN: The owner of the mutex is dead ...\n");
            shared_mutex_make_consistent(obj);
            fprintf(stdout, "INFO: I'm the new owner!\n");
            shared_mem_setowner(obj->shm, TRUE);
            return;
        }
#endif
        fprintf(stderr, "ERROR: Locking the mutex failed: %s\n", strerror(ret));
        exit(1);
    }
}

/* shared_mutex_unlock: To unlock the mutex */
void shared_mutex_unlock(struct shared_mutex_t* obj)
{
    int ret;

    if ((ret = pthread_mutex_unlock(obj->ptr))) {
        fprintf(stderr, "ERROR: Unlocking the mutex failed: %s\n", strerror(ret));
        exit(1);
    }
}

#if !defined(__APPLE__)
/* shared_mutex_make_consistent: Make consistent the shared mutex */
void shared_mutex_make_consistent(struct shared_mutex_t* obj)
{
    int ret;

    if ((ret = pthread_mutex_consistent(obj->ptr)))
        fprintf(stderr, "ERROR: Making the mutex consistent failed: %s\n", strerror(ret));
    
}
#endif
