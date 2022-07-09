# Threads
Every thread is initiated by a process. It will then belong to that process forever. It is not possible to have a shared thread or transfer the ownership of a thread to another process. Every process has at least one thread that is its main thread. In a C program, the main function is executed as part of the main thread.

All the threads share the same Process ID (PID). If you use utilities like top or htop, you can easily see the threads are sharing the same process ID, and are grouped under it. More than that, all the attributes of the owner process are inherited by all of its threads for example, group ID, user ID, current working directory, and signal handlers. As an example, the current working directory of a thread is the same as its owner process.

Every thread has a unique and dedicated Thread ID (TID). This ID can be used to pass signals to that thread or track it while debugging. You will see that in POSIX threads, the thread ID is accessible via the pthread_t variable. In addition, every thread has also a dedicated signal mask that can be used to filter out the signals it may receive.





