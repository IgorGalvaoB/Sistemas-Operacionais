#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 5 /* qtdade de filosofos */
#define TAKEN 1
#define NOT_TAKEN 0

sem_t mutex;
int forks[N];

pthread_t tid[N];
void take_fork(int f, int g);
void put_fork(int f, int g);
void think(int i);
void eat(int i);

void philosopher(int i)
{

    while (1)
    {
        think(i);
        sem_wait(&mutex);
        printf("esperando1\n");
        take_fork(i, i);
        take_fork(i, (i + 1) % N);
        sem_post(&mutex);
        eat(i);
        sem_wait(&mutex);
        printf("esperando2\n");
        put_fork(i, i);
        put_fork(i, (i + 1) % N);
        sem_post(&mutex);
    }
}

void think(int i)
{

    sleep(1);

    return;
}

void take_fork(int f, int g)
{
    forks[g] = TAKEN;
}

void eat(int i)
{
    sleep(1);
    return;
}

void put_fork(int f, int g)
{

    forks[g] = NOT_TAKEN;
}

int main(int argc, char *argv[])

{

    int i;

    int p[N];
    
    for (i = 0; i < N; i++)
    {

        forks[i] = NOT_TAKEN;

        p[i] = i;
    }

    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)

        pthread_create(&tid[i], NULL, (void *)philosopher, (int *)(size_t)p[i]);

    for (i = 0; i < N; i++)

        pthread_join(tid[i], NULL);

    sem_destroy(&mutex);

    exit(0);
}
