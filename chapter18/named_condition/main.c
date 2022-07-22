#include <stdio.h>


/* signal library */
#include <signal.h>

/* For exit the program */
#include <stdlib.h>

/* Include the unix library */
#include <unistd.h>

/* include the headers */
#include "shared_mutex.h"
#include "shared_memory.h"
#include "shared_condition.h"

/* Include the instance of counter */
#include "integer_counter.h"


int int_received = 0;
struct shared_cond_t *cond = NULL;
struct shared_mutex_t *mutex = NULL;

/* sigint_handler: The func process handler */
void sigint_handler(int signo)
{
    fprintf(stdout, "\nHandling INT signal: %d ...\n", signo);
    int_received = 1;
}


int main(int argc, char *argv[])
{
    int my_number;
    struct shared_int32_t *counter; 
    
    signal(SIGINT, sigint_handler);

    if (argc < 2) {
        fprintf(stderr, "ERROR: You have to provide the process number.\n");
        exit(1);
    }

    /* Get the number */
    my_number = atol(argv[1]);
    printf("My number is %d!\n", my_number);


    /* Create the suprem instance to count */
    counter = shared_int32_new();
    
    /* Create the shared memory */
    shared_int32_ctor(counter, "/counter0");
    
    /* initialize the variable */
    shared_int32_setvalue_ifowner(counter, 1);

    /* Create the mutex instance */
    mutex = shared_mutex_new();
    shared_mutex_ctor(mutex, "/mutex0");

    /* Create the shared instance */
    cond = shared_cond_new();
    shared_cond_ctor(cond, "/cond0");

    /* Lock the process */
    shared_mutex_lock(mutex);

    while (shared_int32_getvalue(counter) < my_number) {
        if (int_received) {
            break;
        }
        printf("Waiting for the signal, just for 5 seconds ...\n");
        shared_cond_timedwait(cond, mutex, 5L * 1000 * 1000 * 1000);
        if (int_received) {
            break;
        }
        printf("Checking condition ...\n");
    }

    if (int_received) {
        printf("Exiting ...\n");
        shared_mutex_unlock(mutex);
        goto destroy;
    }

    /* Increment the number */
    shared_int32_setvalue(counter, my_number + 1);
    printf("My turn! %d ...\n", my_number);
    
    shared_mutex_unlock(mutex);
    sleep(1);

    /* Make the broadcasting */
    shared_cond_broadcast(cond);

    /* Destroy every thing */
 destroy:
    shared_cond_dtor(cond);
    shared_cond_delete(cond);
    
    shared_mutex_dtor(mutex);
    shared_mutex_delete(mutex);

    shared_int32_dtor(counter);
    shared_int32_delete(counter);
    
    
    return 0;
}





