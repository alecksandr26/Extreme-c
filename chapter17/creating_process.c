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

    if (ret) /* Child process */
        say_hello("Child process", ret);
        
    else /* Father process */
        say_hello("Father process", getpid());

    printf("Type CTRL-C to exit ...\n");
    
    while (1)
        ;
    
    return 0;
}





