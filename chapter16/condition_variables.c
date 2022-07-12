#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Condition variable  */
#include <pthread.h>

typedef struct shared_state_t {
    /* The variable to know if 'A' was printed */
    bool done;

    /* mutex object to protec the critical sections */
    pthread_mutex_t mtx;

    /* Condition Variable to synchronize the two threads */
    pthread_cond_t cv;
} SharedState;


/* Init the object state */
void shared_state_init(SharedState *shared_state)
{
    shared_state->done = false;
    pthread_mutex_init(&shared_state->mtx, NULL);
    pthread_cond_init(&shared_state->cv, NULL);
}


/* Destroy the object state */
void shared_state_destroy(SharedState *shared_state)
{
    pthread_mutex_destroy(&shared_state->mtx);
    pthread_cond_destroy(&shared_state->cv);
}


/* The first thread sequence */
void thread_body_1(SharedState *state)
{
    /* First process some stuff ... */
    
    pthread_mutex_lock(&state->mtx);
        
    printf("Hello, ");
    state->done = true;

    /* Send the signal of finish */
    pthread_cond_signal(&state->cv);
    pthread_mutex_unlock(&state->mtx);

    /* Continue processing other stuff ... */
}


/* The second thread sequence */
void thread_body_2(SharedState *state)
{
    /* First process some stuff ... */
    
    pthread_mutex_lock(&state->mtx);
    
    /* Wait until flag becames true  just in the case that thread2 gets
       execute first */
    while (!state->done)
        /* Wait for the condition variable and wake up the antoher thread */
        pthread_cond_wait(&state->cv, &state->mtx);
    
    printf("World!!\n");
    pthread_mutex_unlock(&state->mtx);

    /* Continue processing other stuff ... */
}


int main()
{
    SharedState state;
    pthread_t t1, t2;
    int res1, res2;
    
    /* Initialize our state object */
    shared_state_init(&state);

    /* Create the threads */
    res1 = pthread_create(&t1, NULL, &thread_body_1, &state);
    res2 = pthread_create(&t2, NULL, &thread_body_2, &state);

    if (res1 || res2) {
        printf("Threads could not be created\n");
        exit(2);
    }


    /* Joined the threads */
    res1 = pthread_join(t1, NULL);
    res2 = pthread_join(t2, NULL);

    if (res1 || res2) {
        printf("Threads could not be joined\n");
        exit(2);
    }

    shared_state_destroy(&state);
        
    return 0;
}
