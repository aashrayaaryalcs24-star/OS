
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;
void* producer(void* arg) {
    for(int i = 0; i < 15; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = i;
        printf("Produced: %d at buffer[%d]\n", i, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}
void* consumer(void* arg) {
    int item;
    for(int i = 0; i < 15; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    return NULL;
}
void run_producer_consumer() {
    pthread_t p, c;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
}
#define N 5
sem_t forks[N];
void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;
    for(int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);
        if (id == N - 1) {
            sem_wait(&forks[right]);
            printf("Philosopher %d picked up right fork %d.\n", id, right);
            sem_wait(&forks[left]);
            printf("Philosopher %d picked up left fork %d.\n", id, left);
        } else {
            sem_wait(&forks[left]);
            printf("Philosopher %d picked up left fork %d.\n", id, left);
            sem_wait(&forks[right]);
            printf("Philosopher %d picked up right fork %d.\n", id, right);
        }
        printf("Philosopher %d is eating.\n", id);
        sleep(2);
        sem_post(&forks[left]);
        sem_post(&forks[right]);
        printf("Philosopher %d put down forks %d and %d.\n", id, left, right);
    }
    return NULL;
}
void run_dining_philosophers() {
    pthread_t ph[N];
    int ids[N];
    for(int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);
    for(int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }
    for(int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);
}
int main() {
    int choice;
    printf("\n--- Synchronization Simulation ---\n");
    printf("1. Producer-Consumer Problem\n");
    printf("2. Dining Philosophers Problem\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if(choice == 1)
        run_producer_consumer();
    else if(choice == 2)
        run_dining_philosophers();
    else
        printf("Invalid choice\n");
    return 0;
}
