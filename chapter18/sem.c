/*
  This example using shared memory to sychronize some variables
*/
#include <stdio.h>

/* Interface of os */
#include <stdlib.h>
#include <unistd.h>

/* To deal with the errors */
#include <string.h>
#include <errno.h>

/* To control the file control */
#include <fcntl.h>

/* For memory mapping */
#include <sys/mman.h>
#include <sys/wait.h>

/* semaphore to synchronize */
#include <semaphore.h>

/* shared memory size */
#define SHARED_MEM_SIZE 4

/* Shared file descriptor used to refer to the shared memory object */
int shared_fd = -1;

/* The pointer to the shared counter */
int32_t* counter = NULL;

/* The pointer to the shared semaphore */
sem_t* semaphore = NULL;



/* init_control_mechanism: This initialize the memory shared */
void init_control_mechanism()
{
    /* Create the semaphore memory */
    semaphore = sem_open("/sem0", O_CREAT | O_EXCL, 0600, 1);

    /* If there is an error */
    if (semaphore == SEM_FAILED) {
        fprintf(stderr, "ERROR: Opening the semaphore failed: %s\n", strerror(errno));
        exit(1);
    }
}


/* shutdown_control_mechanism: Close the shared memory  */
void shutdown_control_mechanism()
{
    /* Close the shared memory */
    if (sem_close(semaphore)) {
        fprintf(stderr, "ERROR: Closing the semaphore failed: %s\n", strerror(errno));
        exit(1);
    }

    /* Delete the shared file */
    if (sem_unlink("/sem0") < 0) {
        fprintf(stderr, "ERROR: Unlinking failed: %s\n", strerror(errno));
        exit(1);
    }
}


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


/* inc_counter: Increment the function to be executed by the two process */
void inc_counter() {
    int32_t temp;
    
    sem_wait(semaphore); /* Modifying critical memory */
    temp = *counter;
    temp++;
    *counter = temp;
    sem_post(semaphore);
}



int main()
{
    void *map;
    pid_t pid;
    
    init_shared_resource();
    init_control_mechanism();


    /* Allocate and truncate the shared memory region */
    if (ftruncate(shared_fd,  SHARED_MEM_SIZE * sizeof(char)) < 0) {
        fprintf(stderr, "ERROR: Truncation failed: %s\n", strerror(errno));
        return 1;
    }
    
    fprintf(stdout, "The memory region is truncated.\n");
    
    /* Map the shared memory and initialize the counter */
    map = mmap(0, SHARED_MEM_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);
    
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        return 1;
    }
    
    counter = (int32_t *) map;
    *counter = 0;

    /* Fork a new process */
    pid = fork();

    if (pid) { /* Parent process */
        /* increment counter */
        inc_counter();
        fprintf(stdout, "The parent process sees the counter as %d.\n", *counter);
    }

    else { /* Child process */
        inc_counter();
        fprintf(stdout, "The child process sees the counter as %d.\n", *counter);
    }


    /* Remove the pointer */
    if (munmap(counter, SHARED_MEM_SIZE) < 0) {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Close the file */
    if (close(shared_fd) < 0) {
        fprintf(stderr, "ERROR: Closing shared memory fd filed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    
    if (pid) { /* parent process shutdown the memory */
        shutdown_shared_resource();
        shutdown_control_mechanism();
    }
    
    return 0;
}





