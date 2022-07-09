#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* Include the functions threads */
#include <pthread.h>


/* This is the function that will be execute by the thread */
void print_hello()
{
    sleep(1);
    printf("Hello I'm in a detach thread!!!!\n");
}


int main()
{
    pthread_t thread;

    /* To create the tread */
    if (pthread_create(&thread, NULL, &print_hello, NULL) != 0) {
        printf("Thread could not be created\n");
        exit(1);
    }

    /* Detach a thread with this new function the main process will not wait to the finish execution of
       the thread */
    if (pthread_detach(thread)) {
        printf("Thread could not be detached\n");
        exit(2);
    }

    printf("Outside the thread\n");

    /* We need to figure out a way to be able to execute all the threads without finishing before the program */
    // sleep(1);

    /* Now using a sleep function is not necessary we can use this function
       With this function the main process will wait until all the detached threads finish
     */
    pthread_exit(NULL);
    
    return 0;
}





