#include <stdio.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>


int main()
{
    char *args[] = {"echo", "Hello, ", "World!", 0};

    /* Execute the new process */
    
    execvp("echo", args);

    printf("execvp() failed. Error: %s\n", strerror(errno));
    
    return 0;
}
