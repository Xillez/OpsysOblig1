#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t signal[6];

struct threadargs
{
    int id;
    int time;
};

void* thread(void *arg)
{
    struct threadargs* targs=arg;
    // Wait to get into critical region
    sem_wait(&signal[targs->id]);
    printf("Thread %d kjører\n", targs->id);
    sleep(targs->time);
    printf("Thread %d kjørte i %d sekunder\n", targs->id, targs->time);
    // Say I'm done!
    sem_post(&signal[targs->id]);

    // Who am I going to wake up
    switch(targs->id)
    {
        // 0, wakes up thread 1 and 4
        case 0: sem_post(&signal[1]); sem_post(&signal[4]); break;
        // 2, waits for 1 by trying to count it's semaphore down, and then starts thread 3
        case 2: sem_wait(&signal[1]); sem_post(&signal[3]); break;
        // 4, starts thread 5
        case 4: sem_post(&signal[5]); break;
        // Any other thread shouldn't do anything
        default: break;
    }

    // Exit thread
    pthread_exit(0);
}

int main(void)
{
    pthread_t threads[6];

    // Immediate Declaration and definition, removed the need to do malloc and loops
    struct threadargs targs[6] = {{0,1}, {1,2}, {2,3}, {3,2}, {4,3}, {5,3}};

    // Loop through the threads, init their semphore, and creates them
    for (int i = 0; i < 6; i++)
    {
        // Thread 0 and 2 should start, no-one else
        sem_init(&signal[i], 0, ((i == 0 || i == 2) ? 1 : 0));
        pthread_create(&threads[i], NULL, thread, (void*) &targs[i]);
    }

    // Wait for all threads
    for (int i = 0; i < 6; i++)
    {
        pthread_join(threads[i], NULL);
    }
    exit(0);
}
