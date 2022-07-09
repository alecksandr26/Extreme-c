#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#include <pthread.h>


void thread_body(char *str)
{
    printf("%s\n", str);
}



int main()
{
    int res1, res2, res3;
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    res1 = pthread_create(&thread1, NULL, &thread_body, "Apple");
    res2 = pthread_create(&thread2, NULL, &thread_body, "Orange");
    res3 = pthread_create(&thread3, NULL, &thread_body, "Lemon");

    if (res1 || res2 || res3) {
        printf("The threads could not be created\n");
        exit(1);
    }

    
    res1 = pthread_join(thread1, NULL);
    res2 = pthread_join(thread2, NULL);
    res3 = pthread_join(thread3, NULL);

    printf("Outside threads\n");

    if (res1 || res2 || res3) {
        printf("The threads could not be joined\n");
        exit(2);
    }
    
    return 0;
}




