#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* The threads library */
#include <pthread.h>


void thread_body(int *shared_var)
{
    while (*(shared_var) <= 100)
        *(shared_var) += 1;

    
    printf("%i\n", *(shared_var));
}



int main()
{
    pthread_t thread1, thread2;
    int shared_var, res1, res2;
    
    res1 = pthread_create(&thread1, NULL, &thread_body, &shared_var);
    res2 = pthread_create(&thread2, NULL, &thread_body, &shared_var);
    
    if (res1 || res2) {
        printf("Threade could not be created \n");
        exit(1);
    }

    /* Set the shared memory */
    shared_var = 0;
    
    res1 = pthread_join(thread1, NULL);
    res2 = pthread_join(thread2, NULL);

    printf("%i\n", shared_var);
    
    if (res1 || res2) {
        printf("Threade could not be detached\n");
        exit(2);
    }
    
    
    return 0;
}




