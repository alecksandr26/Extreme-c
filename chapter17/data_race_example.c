/* This is an example with fork how we can evoke a data race */
#include <stdio.h>

/* For data type */
#include <stdint.h>

/* For exit */
#include <stdlib.h>

/* For file cotnrol */
#include <fcntl.h>
#include <unistd.h>

/* For error managing */
#include <errno.h>
#include <string.h>

/* For memory mapping */
#include <sys/mman.h>
#include <sys/wait.h>


/* The amount of bytes that we want to shared */
#define SH_SIZE 4


int shared_fd; /* file descriptor */

/* The pointer to the shared memory */
int32_t *counter;

/* init_shared_resource: Open or create the shared object */
void init_shared_resource()
{
    /* Create the shared object */
    shared_fd = shm_open("shm0", O_CREAT | O_RDWR, 0600);

    if (shared_fd < 0) { /* Error if can't opened or created it */
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Shared memory is created with fd: %d\n", shared_fd);
}


/* shutdown_shared_resource: Shutdown the shared memory */
void shutdown_shared_resource()
{
    /* To release the memory */
    if (shm_unlink("/shm0") < 0) {
        fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}


/* inc_counter: Increment the value from the shared memory */
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
    
    /* Initialize the variables */
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

    /* Get the pointer */
    map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);

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
        usleep(1);
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


