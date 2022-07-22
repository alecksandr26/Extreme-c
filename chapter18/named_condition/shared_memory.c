#include <stdio.h>

/* For deailng with errors */
#include <errno.h>
#include <string.h>
#include <stdlib.h>


/* For manipuling the shared memory */
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

/* Include the class */
#include "shared_memory_p.h"

#define TRUE 1
#define FALSE 0

bool_t owner_process_set = FALSE;
bool_t owner_process = FALSE;

/* shared_mem_new: Create a new instance of the memory */
struct shared_mem_t* shared_mem_new()
{
    return (struct shared_mem_t *) malloc(sizeof(struct shared_mem_t));
}
/* shared_mem_delete: To delete the shared memory */
void shared_mem_delete(struct shared_mem_t* obj)
{
    free(obj->name);
    free(obj);
}

/* shared_mem_ctor: Contruct all the memory */
void shared_mem_ctor(struct shared_mem_t* obj, const char* name, size_t size)
{
    obj->size = size;
    obj->name = (char*)malloc(strlen(name) + 1);
    strcpy(obj->name, name);
    obj->shm_fd = shm_open(obj->name, O_RDWR, 0600);

    /* Check if we are the owner process */
    if (obj->shm_fd >= 0) { /* if it already exist */
        if (!owner_process_set) { /* To know if the process is the owner */
            owner_process = FALSE;
            owner_process_set = TRUE;
        }
        printf("The shared memory %s is opened.\n", obj->name);
    } else if (errno == ENOENT) { /* if that shared object file doesn't exist */
        printf("WARN: The shared memory %s does not exist.\n", obj->name);
        obj->shm_fd = shm_open(obj->name, O_CREAT | O_RDWR, 0600);
        if (obj->shm_fd >= 0) {
            /* Its important if we are the owner of this shared memory file */
            if (!owner_process_set) {
                owner_process = TRUE;
                owner_process_set = TRUE;
            }
            printf("The shared memory %s is created and opened.\n", obj->name);

            /* Truncate the size of shared memory we want */
            if (ftruncate(obj->shm_fd, obj->size) < 0) {
                fprintf(stderr, "ERROR(%s): Truncation failed: %s\n", obj->name, strerror(errno));
                exit(1);
            }
            
        } else {
            fprintf(stderr, "ERROR(%s): Failed to create shared memory: %s\n", obj->name, strerror(errno));
            exit(1);
        }
    } else {
        fprintf(stderr, "ERROR(%s): Failed to create shared memory: %s\n", obj->name, strerror(errno));
        exit(1);
    }

    /* map the memory */
    obj->map_ptr = mmap(0, obj->size, PROT_READ | PROT_WRITE, MAP_SHARED, obj->shm_fd, 0);

    if (obj->map_ptr == MAP_FAILED) {
        fprintf(stderr, "ERROR(%s): Mapping failed: %s\n",name, strerror(errno));
        exit(1);
    }

    /* Here We get the pointer ready for use */
    obj->ptr = (char *) obj->map_ptr;
}

/* shared_mem_dtor: deconsturct an instance of the memory */
void shared_mem_dtor(struct shared_mem_t* obj)
{
    /* Remove the pointer into the map */
    if (munmap(obj->map_ptr, obj->size) < 0) {
        fprintf(stderr, "ERROR(%s): Unmapping failed: %s\n", obj->name, strerror(errno));
        exit(1);
    }
    printf("The shared memory %s is unmapped.\n", obj->name);

    /* close the shared file from the process */
    if (close(obj->shm_fd) < 0) {
        fprintf(stderr, "ERROR(%s): Closing the shared memory fd failed: %s\n", obj->name, strerror(errno));
        exit(1);
    }

    printf("The shared memory %s is closed.\n", obj->name);
    
    /* If this is the owner process of this memory */
    if (owner_process) {
        /* Deletes the file finishing and destroying that memory */
        if (shm_unlink(obj->name) < 0) {
            fprintf(stderr, "ERROR(%s): Unlinking the shared memory failed: %s\n",obj->name, strerror(errno));
            exit(1);
        }
        printf("The shared memory %s is deleted.\n", obj->name);
    }
}

/* shared_mem_getptr: Gets the pointer of the shared memory  */
char* shared_mem_getptr(struct shared_mem_t* obj)
{
    return obj->ptr;
}

/* shared_mem_isowner: To know if we are the owner of the shared memory */
bool_t shared_mem_isowner(struct shared_mem_t* obj)
{
    return owner_process;
}

/* shared_mem_setowner: To set that shared memory to this new process */
void shared_mem_setowner(struct shared_mem_t* obj, bool_t is_owner)
{
    owner_process = is_owner;
}

