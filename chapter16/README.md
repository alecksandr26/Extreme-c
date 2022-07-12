# Thread Synchronization
In this chapter, we will cover the following topics:

- Using POSIX mutexes to protect critical sections accessing a shared
resource.
- Using POSIX condition variables to wait for a specific condition.
- Using various types of locks together with mutexes and condition variables.
- Using POSIX barriers and the way they can help synchronize a number
of threads.
- The concept of the semaphore and its counterpart object in the pthread
library: the POSIX semaphore. You are going to find out that mutexes
are just binary semaphores.
- The memory structure of a thread and how this structure can affect
memory visibility in a multi-core system.
