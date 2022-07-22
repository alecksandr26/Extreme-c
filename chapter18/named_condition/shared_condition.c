#include <stdio.h>

/* Fo errors */
#include <string.h>
#include <errno.h>

/* For memory allcoation */
#include <stdlib.h>

/* For pthread condition variable */
#include <pthread.h>

/* For timing */
#include <time.h>

#include "shared_condition_p.h"
#include "shared_mutex_p.h"
#include "shared_memory_p.h"


struct shared_cond_t *shared_cond_new()
{
    struct shared_cond_t *obj = (struct shared_cond_t *) malloc(sizeof(struct shared_cond_t));
    obj->shm = shared_mem_new();
    return obj;
}

void shared_cond_delete(struct shared_cond_t* obj)
{
    shared_mem_delete(obj->shm);
    free(obj);
}

void shared_cond_ctor(struct shared_cond_t* obj, const char* name)
{
    pthread_condattr_t cond_attr;
    int ret;
    
    shared_mem_ctor(obj->shm, name, sizeof(pthread_cond_t));
    obj->ptr = (pthread_cond_t *)shared_mem_getptr(obj->shm);
    if (shared_mem_isowner(obj->shm)) {
        if ((ret = pthread_condattr_init(&cond_attr))) {
            fprintf(stderr, "ERROR(%s): Initializing cv attrs failed: %s\n", name, strerror(ret));
            exit(1);
        }
        if ((ret = pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED))) {
            fprintf(stderr, "ERROR(%s): Setting as process shared failed: %s\n", name, strerror(ret));
            exit(1);
        }
        if ((ret = pthread_cond_init(obj->ptr, &cond_attr))) {
            fprintf(stderr, "ERROR(%s): Initializing the cv failed: %s\n", name, strerror(ret));
            exit(1);
        }
        if ((ret = pthread_condattr_destroy(&cond_attr))) {
            fprintf(stderr, "ERROR(%s): Destruction of cond attrs failed: %s\n", name, strerror(ret));
            exit(1);
        }
    }
}

void shared_cond_dtor(struct shared_cond_t* obj)
{
    int ret;
    
    if (shared_mem_isowner(obj->shm))
        if ((ret = pthread_cond_destroy(obj->ptr)))
            fprintf(stderr, "WARN: Destruction of the cv failed: %s\n", strerror(ret));
    
    shared_mem_dtor(obj->shm);
}

void shared_cond_wait(struct shared_cond_t* obj, struct shared_mutex_t* mutex)
{
    int ret;

    if ((ret = pthread_cond_wait(obj->ptr, shared_mutex_getptr(mutex)))) {
        fprintf(stderr, "ERROR: Waiting on the cv failed: %s\n", strerror(ret));
        exit(1);
    }
}

void shared_cond_timedwait(struct shared_cond_t* obj, struct shared_mutex_t* mutex, long int time_nanosec)
{
    struct timespec ts;
    int ret;

    ts.tv_sec = ts.tv_nsec = 0;
    if ((ret = clock_gettime(CLOCK_REALTIME, &ts))) {
        fprintf(stderr, "ERROR: Failed at reading current time: %s\n", strerror(errno));
        exit(1);
    }
    
    ts.tv_sec += (int)(time_nanosec / (1000L * 1000 * 1000));
    ts.tv_nsec += time_nanosec % (1000L * 1000 * 1000);

    if ((ret = pthread_cond_timedwait(obj->ptr, shared_mutex_getptr(mutex), &ts))) {
#if !defined(__APPLE__)
        if (ret == EOWNERDEAD) {
            fprintf(stderr, "WARN: The owner of the cv's mutex is dead ...\n");
            shared_mutex_make_consistent(mutex);
            fprintf(stdout, "INFO: I'm the new owner!\n");
            shared_mem_setowner(obj->shm, TRUE);
            return;
        } else if (ret == ETIMEDOUT) {
#else
            if (ret == ETIMEDOUT) {
#endif
            return;
        }
        fprintf(stderr, "ERROR: Waiting on the cv failed: %s\n", strerror(ret));
        exit(1);
    }
}

void shared_cond_broadcast(struct shared_cond_t* obj)
{
    int ret;

    if ((ret = pthread_cond_broadcast(obj->ptr))) {
        fprintf(stderr, "ERROR: Broadcasting on the cv failed: %s\n", strerror(ret));
        exit(1);
    }
}

