/* This is an example of data race but now with fork and with file system memory */
#include <stdio.h>

/* For exit */
#include <stdlib.h>

/* For pointers */
#include <stdint.h>

/* For opening the shared state and the fork */
#include <unistd.h>
#include <fcntl.h>

/* For error handling */
#include <string.h>
#include <errno.h>

/* And for memory */
#include <sys/mman.h>
#include <sys/wait.h>

/* The amount of bytes from our counter */
#define SH_SIZE 4

/* The shared file descriptor used to refer to the shared file */
int shared_fd;

/* The pointer to the shared counter */
int32_t* counter;


/* init_shared_resource: Inits the shared resource of the data */
void init_shared_resource()
{
    /* Creates the file */
    shared_fd = open("data.bin", O_CREAT | O_RDWR, 0600);

    if (shared_fd < 0) {
        fprintf(stderr, "ERROR: Failed to create the file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Shared memory is created with fd: %d\n", shared_fd);
}


/* shutdown_shared_resource: Deletes the file basically the shared memory */
void shutdown_shared_resource()
{
    if (remove("data.bin") < 0) {
        fprintf(stderr, "ERROR: Removing the file failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}


/* inc_counter: Increments the the value data */
void inc_counter()
{
    int32_t temp;

    /* use usleep to synchronize */
    usleep(1);
    temp = *counter;
    usleep(1);
    temp++;
    usleep(1);
    *counter = temp; /* increment just one time */
    usleep(1);
}


int main()
{
    void *map;
    pid_t pid;
    
    shared_fd = -1;
    counter = NULL;

    /* The parent create the memory */
    init_shared_resource();

     /* Resize the files */
    if (ftruncate(shared_fd, SH_SIZE * sizeof(char)) < 0) {
        fprintf(stderr, "ERROR: Truncation failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "The memory region is truncated\n");

    /* Get the pointer and map the memory */
    map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);

    /* Print */
    printf("%p\n", map);
    printf("%p, \n", &pid);

    /* Check if there is an error */
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Get the variables */
    counter = (int32_t *) map;
    *counter = 0;

    /* Create a child process */
    pid = fork();

    if (pid) { /* Parent process */
        inc_counter(); /* Increment the variable */
        fprintf(stdout, "The parent process sees the counter as %i\n", *counter);
    } else { /* Child process */
        inc_counter(); /* Increment the variable */
        fprintf(stdout, "The child process sees the counter as %d.\n", *counter);
    }

    /* Remove the pointer */
    if (munmap(counter, SH_SIZE) < 0) {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Close the file */
    if (close(shared_fd) < 0) {
        fprintf(stderr, "ERROR: Closing shared memory fd filed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }


    /* Only the parent can shutdown the memory */
    if (pid)
        shutdown_shared_resource();
    
    return 0;
}
