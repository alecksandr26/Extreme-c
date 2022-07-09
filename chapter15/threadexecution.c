#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* To execute a posix thread */
#include <pthread.h>

/* This is the function that will be execute by the thread */
void print_hello()
{
    sleep(1);
    printf("Hello I'm in a thread!!!!\n");
}
    


int main()
{
    /* Thread handler */
    pthread_t thread;


    /* To create the tread */
    if (pthread_create(&thread, NULL, &print_hello, NULL) != 0) {
        printf("Thread could not be created\n");
        exit(1);
    }

    /* Now lets run the thread by executing this func the main process will wait until
       it finish with its execution */
    if (pthread_join(thread, NULL)) {
        printf("Thread could not be joined\n");
        exit(2);
    }

    printf("Outside the thread\n");
        
    return 0;
}




