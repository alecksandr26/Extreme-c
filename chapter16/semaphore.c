#include <stdio.h>
#include <stdlib.h>

/* The threads library of posix */
#include <pthread.h>


/* The semaphore */
#include <semaphore.h>


/* semaphore address */
sem_t *semaphore;

/* So semaphores works as a mutex with the difference of support multiple threads and have an order */


void thread_body(int *shared_var)
{
    /* Wait the semaphore */
    sem_wait(semaphore);

    /* increment the variable */
    (*shared_var)++;

    /* release the semaphore */
    sem_post(semaphore);
}

int main()
{
    int shared_var, res1, res2;
    pthread_t t1, t2;
    
#ifdef __APPLE__
    // Unnamed semaphores are not supported in OS/X. Therefore
    // we need to initialize the semaphore like a named one using
    // sem_open function.
    semaphore = sem_open("sem0", O_CREAT | O_EXCL, 0644, 1);
    
#else
    sem_t local_semaphore;
    semaphore = &local_semaphore;
    // Initiliaze the semaphore as a mutex (binary semaphore)
    sem_init(semaphore, 0, 1);
#endif

    shared_var = 0;

    /* Create the threads */
    res1 = pthread_create(&t1, NULL, &thread_body, &shared_var);
    res2 = pthread_create(&t2, NULL, &thread_body, &shared_var);

    if (res1 || res2) {
        printf("The threads could not be created\n");
        exit(1);
    }


    // Wait for the threads to finish
    res1 = pthread_join(t1, NULL);
    res2 = pthread_join(t2, NULL);

    if (res1 || res2) {
        printf("The threads could not be joined\n");
        exit(2);
    }

    printf("%i\n", shared_var);

#ifdef __APPLE__
    sem_close(semaphore);
#else
    sem_destroy(semaphore);
#endif
    

    return 0;
}
