/* This is an exmaple of how two process can shared memory
   This shared memory will be continue allocated into the ram
 */


#include <stdio.h>

/* error handling */
#include <string.h>
#include <errno.h>

/* File control */
#include <fcntl.h>

/* For the memory shared object */
#include <sys/mman.h>

/* And for truncate functions */
#include <unistd.h>


#define SH_SIZE 16


int main()
{
    /* This is the file descriptor */
    int shm_fd;
    void *map;
    char *ptr;

    /* Open or create the shared memory
       This file will be allocate into the path /dev/shm/shm0
     */
    shm_fd = shm_open("shm0", O_CREAT | O_RDWR, 0600);
    
    if (shm_fd < 0) {
        fprintf(stderr, "ERROR: Failed to create the shared memory: %s\n", strerror(errno));
        return -1;
    }

    fprintf(stdout, "Shared memory is created withd fd: %i\n", shm_fd);

    /* Now truncate the size of the shared memory */
    if (ftruncate(shm_fd, SH_SIZE * sizeof(char)) <  0) {
        fprintf(stderr, "ERROR: Failed to truncate the shared memory: %s\n", strerror(errno));
        return -1;
    }

    fprintf(stdout, "The memory region is truncated\n");

    /* Now we are going to get a pointer to write in that shared memory */
    map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        return 1;
    }

    /* Extract the pointer */
    ptr = (char *) map;

    /* paste the memory */
    strcpy(ptr, "Hello\n");

    fprintf(stdout, "Data is written to the shared memory\n");

    /* Now we are going to unmapping the memory */
    if (munmap(map, SH_SIZE) < 0) {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        return -1;
    }

    /* Now we are going to close the memory */
    if (close(shm_fd) < 0) {
        fprintf(stderr, "ERROR: Closing shared memory failed: %s\n", strerror(errno));
        return -1;
    }


    /* Now free the memory */
    if (shm_unlink("/shm0") < 0) {
        fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n", strerror(errno));
        return -1;
    }


    fprintf(stdout, "The shared memory was release!\n");
   
    return 0;
}


