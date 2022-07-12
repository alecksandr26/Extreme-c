#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_spinlock_t spin;



void thread_body_sum(int *shared_data)
{
    int i;

    for (i = 0; i < 100; ++i) {
        /* Will wait in a loop untile unlock */
        pthread_spin_lock(&spin);
        (*shared_data)++;
        pthread_spin_unlock(&spin);
    }
}


int main()
{
    pthread_t t1, t2;
    int shared_data, res1, res2;

    shared_data = 0;
    
    /* Initialize as private process */
    pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);
    
    res1 = pthread_create(&t1, NULL, &thread_body_sum, &shared_data);
    res2 = pthread_create(&t2, NULL, &thread_body_sum, &shared_data);

    if (res1 || res2) {
        printf("Some threads could not be created\n");
        exit(1);
    }


    /* Finishing with the threads */
    
    res1 = pthread_join(t1, NULL);
    res2 = pthread_join(t2, NULL);

    if (res1 || res2) {
        printf("Some threads could not be joined\n");
        exit(2);
    }

    printf("%i\n", shared_data);

    pthread_spin_destroy(&spin);

    
    return 0;
}
