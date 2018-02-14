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

#define NR_PRINTS 10

struct pargs
{
    int nr;
};

pthread_t philosophers[N];
int state[N];
sem_t mutex;
sem_t s[N];
sem_t printing;

void* philosopher(void* pargs);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void eat(int i);
void think();

void eat(int i)
{
    // Print the states of all philosophers in a critical area
    sem_wait(&printing);
    for (int a = 0; a < N; a++)
    {
        printf("%s  ", ((state[a] == HUNGRY) ? "HUNGRY" : ((state[a] == THINKING) ? "THINKING" : "EATING")));
    }
    printf("\n");
    sem_post(&printing);
    
    // Eat for random amount of time
    sleep(rand() % 2);
}

void think()
{
    // Think for random amount of time
    sleep(rand() % 2);
}

void* philosopher(void* pargs)
{
    int nrPrints = 0;

    // Get arguments
    struct pargs* args = (struct pargs*) pargs;

    while (nrPrints < NR_PRINTS)
    {
        think();
        take_forks(args->nr);
        eat(args->nr);
        put_forks(args->nr);
        
        nrPrints++;
    }
    return 0;
}

void take_forks(int i)
{
    // Wait to go in critical region
    sem_wait(&mutex);
    // I'm hungry
    state[i] = HUNGRY;
    test(i);
    // I'm finished with critical region
    sem_post(&mutex);
    sem_wait(&s[i]);
}

void put_forks(int i)
{
    // Wait to go in critical region
    sem_wait(&mutex);
    // I'm thinking
    state[i] = THINKING;
    // Tell the others if hungry they can eat
    test(LEFT);
    test(RIGHT);
    // I'm finished with critical region
    sem_post(&mutex);
}

void test(int i)
{
    // If I'm HUNGRY and no neightbours are eating
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        // I eat
        state[i] = EATING;
        sem_post(&s[i]);
    }
}

int main()
{
    int i = 0;
    sem_init(&mutex, 0, 1);
    sem_init(&printing, 0, 1);
    srand(time(NULL));
    //struct pargs* args[N];'
    struct pargs args[N];
    // Loop through the philosophers, init their semphore, and creates them
    for (i = 0; i < N; i++)
    {
        // Define nr argument
        args[i].nr = i;

        // Set ininitial start state and create threads
        sem_init(&s[i], 0, 0);
        pthread_create(&philosophers[i], NULL, philosopher, (void*) &args[i]);
    }

    // Wait for all philosophers
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
    exit(0);
}