#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct thread_data_t {
    int number;
    int res;
} ThreadData;



/* Simple factorial function */
void thread_body_fac(ThreadData *data)
{
    int res, num;

    num = data->number;

    for (data->res = num--; num > 1; num--)
        data->res *= num;
}



int main()
{
    int i, res, res_thread, amount_threads;

    printf("How many factorials do you want to calculate ?\n");
    printf(">>> ");
    scanf("%i", &amount_threads);


    pthread_t threads[amount_threads];
    ThreadData data[amount_threads];

    for (i = 0; i < amount_threads; ++i) {
        printf("nums[%i] = ", i);
        scanf("%i", &data[i].number);
    }

    for (i = 0; i < amount_threads; ++i) {
        res = pthread_create(&threads[i], NULL, &thread_body_fac, &data[i]);
        if (res) {
            printf("Thread could not be created\n");
            exit(1);
        }
    }

    puts("Results");
    for (i = 0; i < amount_threads; ++i) {
        res = pthread_join(threads[i], NULL);
        
        if (res) {
            printf("Thread could not be joined\n");
            exit(2);
        }

        printf("fac(%i) = %i\n", data[i].number, data[i].res);
    }
    
    return 0;
}

