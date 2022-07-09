#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

    /* Created a secure memory frame for each tread */
    char str1[8], str2[8], str3[8];
    strcpy(str1, "Apple");
    strcpy(str2, "Orange");
    strcpy(str3, "Lemon");

    res1 = pthread_create(&thread1, NULL, &thread_body, str1);
    res2 = pthread_create(&thread2, NULL, &thread_body, str2);
    res3 = pthread_create(&thread3, NULL, &thread_body, str3);

    if (res1 || res2 || res3) {
        printf("The threads could not be created\n");
        exit(1);
    }

    
    res1 = pthread_detach(thread1);
    res2 = pthread_detach(thread2);
    res3 = pthread_detach(thread3);

    printf("Outside threads\n");

    if (res1 || res2 || res3) {
        printf("The threads could not be detached\n");
        exit(2);
    }


    // Now, the strings become deallocated.
    pthread_exit(NULL);
    
    return 0;
}





