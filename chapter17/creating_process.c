#include <stdio.h>

/* To get the function fork */
#include <unistd.h>


/* To say hello */
void say_hello(char *name, pid_t i)
{
    printf("Hello, im %s and this is my id %i\n", name, i);
}



int main()
{
    /* To catch the id from the child process */
    pid_t ret;

    printf("Before calling fork ...\n");
    ret = fork();
    
    if (ret) { /* Father process */
        say_hello("Father process", getpid());
        printf("Child process spawned %i\n", ret);
    }
        
    else {/* Child process */
        say_hello("Child process", getpid());
        return 0; /* Return and finish the program */
    }

    
    return 0;
}





