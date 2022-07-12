#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* The threads library */
#include <pthread.h>

/* And the mutex object */
pthread_mutex_t mtx;


void thread_body(int *shared_var)
{
    int i;
    
    for (i = 0; i < 100; ++i) {
        /* The thread will sleep until unlock */
        pthread_mutex_lock(&mtx);
        
        *(shared_var) += 1;
        
        pthread_mutex_unlock(&mtx);
    }
}



int main()
{
    pthread_t thread1, thread2;
    int shared_var, res1, res2;

    /* Set the shared memory */
    shared_var = 0;

    pthread_mutex_init(&mtx, NULL);
    
    res1 = pthread_create(&thread1, NULL, &thread_body, &shared_var);
    res2 = pthread_create(&thread2, NULL, &thread_body, &shared_var);
    
    if (res1 || res2) {
        printf("Threade could not be created \n");
        exit(1);
    }
    
    res1 = pthread_join(thread1, NULL);
    res2 = pthread_join(thread2, NULL);
        
    if (res1 || res2) {
        printf("Threade could not be detached\n");
        exit(2);
    }

    printf("%i\n", shared_var);

    pthread_mutex_destroy(&mtx);
    
    return 0;
}




