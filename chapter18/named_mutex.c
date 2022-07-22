#include <stdio.h>

/* The stdlib */
#include <stdlib.h>
#include <unistd.h>

/* For the errors */
#include <string.h>
#include <errno.h>

/* For the files */
#include <fcntl.h>

/* For mapping the memory */
#include <sys/mman.h>
#include <sys/wait.h>


/* For the */
#include <pthread.h>

#define SHARED_MEM_SIZE 4

/* Shared file descriptor used to refer to shared memory object */
int shared_fd = -1;


/* Shared memory mutex */
int mutex_shm_fd = -1;

/* The pointer for the counter */
int32_t* counter = NULL;

/* pthread pointer */
pthread_mutex_t* mutex = NULL;



/* Inititalize the mutex from shared memory among process */

/* init_control_mechanism: To initialize the mechanism of shared memory */
void init_control_mechanism()
{
    pthread_mutexattr_t attr;
    void *map;
    int ret;
    
    /* Open a shared file mutex */
    mutex_shm_fd = shm_open("/mutex0", O_CREAT | O_RDWR, 0600);
    if (mutex_shm_fd < 0) {
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    }

    /* Prepare the memory */
    if (ftruncate(mutex_shm_fd, sizeof(pthread_mutex_t)) < 0) {
        fprintf(stderr, "ERROR: Truncation of mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    /* Map the memory */
    map = mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, mutex_shm_fd, 0);
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(1);
    }

    /* Create a pointer */
    mutex = (pthread_mutex_t *) map;

    /* Now we need to initialize the pthread mutex */
    ret = -1;
    if ((ret = pthread_mutexattr_init(&attr))) {
        fprintf(stderr, "ERROR: Failed to init mutex attrs: %s\n", strerror(ret));
        exit(1);
    }

    /* Set the configuration to shared the mutex among process */
    if ((ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED))) {
        fprintf(stderr, "ERROR: Failed to set the mutex attr: %s\n", strerror(ret));
        exit(1);
    }

    /* Initialize the mutex */
    if ((ret = pthread_mutex_init(mutex, &attr))) {
        fprintf(stderr, "ERROR: Initializing the mutex failed: %s\n", strerror(ret));
        exit(1);
    }

    /* Destroy the mutex attribute */
    if ((ret = pthread_mutexattr_destroy(&attr))) {
        fprintf(stderr, "ERROR: Failed to destroy mutex attrs : %s\n", strerror(ret));
        exit(1);
    }
}

/* shutdown_control_mechanism: To shutdown the mechanism of shared mutex */
void shutdown_control_mechanism()
{
    int ret;

    /* Destroy the mutex */
    if ((ret = pthread_mutex_destroy(mutex))) {
        fprintf(stderr, "ERROR: Failed to destroy mutex: %s\n", strerror(ret));
        exit(1);
    }

    /* unmapping the memory of the mutex */
    if (munmap(mutex, sizeof(pthread_mutex_t)) < 0) {
        fprintf(stderr, "ERROR: Unmapping the mutex failed: %s\n",strerror(errno));
        exit(1);
    }

    /* close the file */
    if (close(mutex_shm_fd) < 0) {
        fprintf(stderr, "ERROR: Closing the mutex failed: %s\n",strerror(errno));
        exit(1);
    }

    /* Delete completly the shared memory */
    if (shm_unlink("/mutex0") < 0) {
        fprintf(stderr, "ERROR: Unlinking the mutex failed: %s\n", strerror(errno));
        exit(1);
    }
}


/* Initialize the shared memory */


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


/* The function to increment all the variable */

/* inc_counter: Increment the function to be executed by the two process */
void inc_counter() {
    int32_t temp;

    pthread_mutex_lock(mutex);
    temp = *counter;
    temp++;
    *counter = temp;
    pthread_mutex_unlock(mutex);
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

    /* Map the shared memory to initialize the counter */
    map = mmap(0, SHARED_MEM_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        return 1;
    }

    counter = (int32_t *) map;
    *counter = 0;

    /* Fork the process */
    pid = fork();

    if (pid) { /* Parent process */
        /* increment counter */
        inc_counter();
        fprintf(stdout, "The parent process sees the counter as %d.\n", *counter);
    } else { /* Child process */
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


