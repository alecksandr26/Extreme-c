#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_mutex_t mtx;
int counter = 0;

void thread_body()
{
    int stack_var;

    pthread_mutex_lock(&mtx);
    /* Show the memory */
    printf("Thread%i Stack Address: %p\n", ++counter, &stack_var);
    
    pthread_mutex_unlock(&mtx);
}



int main()
{
    pthread_t t1, t2;
    int *res, res2;
    
    pthread_mutex_init(&mtx, NULL);

    res = (int *) malloc(sizeof(int));

    printf("Main Thread Stack Address: %p\n", &t1);
    printf("Main Thread Heap Address: %p\n", res);
    puts("-----------");
    
    res = pthread_create(&t1, NULL, &thread_body, NULL);
    res2 = pthread_create(&t2, NULL, &thread_body, NULL);

    if (res || res2) {
        printf("Threads could not be created\n");
        exit(1);
    }

    res = pthread_join(t1, NULL);
    res2 = pthread_join(t2, NULL);

    if (res || res2) {
        printf("Threads could not not be joined\n");
        exit(2);
    }

    pthread_mutex_destroy(&mtx);

    return 0;
}




