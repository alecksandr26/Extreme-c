#include <stdio.h>
#include <stdlib.h>


#include <pthread.h>


static pthread_barrier_t barrier;


void thread_body_1()
{
    printf("Hello, ");

    /* Wait to the another part finishes with their execution */
    pthread_barrier_wait(&barrier);

    /* Continue processing here */
}


void thread_body_2()
{
    /* First prcess something here */

    /* wait until the another part finishes with their execution */
    pthread_barrier_wait(&barrier);
    
    printf("World!!\n");
}


int main()
{
    pthread_t t1, t2;
    int res1, res2;

    /* Init the barrier with the number of threads we want to sync */
    pthread_barrier_init(&barrier, NULL, 2);

    res1 = pthread_create(&t1, NULL, &thread_body_1, NULL);
    res2 = pthread_create(&t2, NULL, &thread_body_2, NULL);

    if (res1 || res2) {
        printf("The threads could not be created\n");
        exit(1);
    }

    res1 = pthread_join(t1, NULL);
    res2 = pthread_join(t2, NULL);

    if (res1 || res2) {
        printf("The threads could not be joined\n");
        exit(2);
    }
    
    /* Destroy the barrier */
    pthread_barrier_destroy(&barrier);
    
    return 0;
}

