#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

struct pargs
{
    int nr;
};

pthread_t philosophers[N];
int state[N];
sem_t mutex;
sem_t s[N];

void* philosopher(void* pargs);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void eat(int i);
void think(int i);

void eat(int i)
{
    int t = rand() % 4;
    printf("Philosopher %d eats for: %d\n", i, t);
    sleep(t);
    printf("Philosopher %d is done eating!\n", i);
}

void think(int i)
{
    sleep(rand() % 4);
}

void* philosopher(void* pargs)
{
    struct pargs* args = (struct pargs*) pargs;
    printf("%d starts!\n", args->nr);
    while (1 == 1)
    {
        think(args->nr);
        take_forks(args->nr);
        eat(args->nr);
        put_forks(args->nr);
    }
    pthread_exit(0);
}

void take_forks(int i)
{
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&s[i]);
}

void put_forks(int i)
{
    sem_wait(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[i] = EATING;
        sem_post(&s[i]);
    }
}

int main()
{
    sem_init(&mutex, 0, 1);
    srand(time(NULL));
    struct pargs* args[N];
    // Loop through the philosophers, init their semphore, and creates them
    for (int i = 0; i < N; i++)
    {
        // Allocate memory to arguments
        args[i] = (struct pargs *)malloc(sizeof(struct pargs));
        args[i]->nr = i;

        // Thread 0 and 2 should start, no-one else
        sem_init(&s[i], 0, 0);
        pthread_create(&philosophers[i], NULL, philosopher, (void* )&args[i]);
    }

    // Wait for all philosophers
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
    exit(0);

    return 0;
}