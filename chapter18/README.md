# Process Synchronization
Despite threads that are bound to a process, processes can live freely on any machine, with any operating system, located anywhere within a network as big as the internet. As you might imagine, things become complicated. It will not be easy to synchronize a number of processes in such a distributed system.
## Named POSIX semaphores 
The same POSIX semaphores that we explained in Chapter 16, Thread Synchronization, but with one difference: they have a name now and can be used globally throughout the system. In other words, they are not anonymous or private semaphores anymore.
