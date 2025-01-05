#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> // Para intptr_t

void *thread_function(void *arg);
int NUM_THREADS = 4;
int i;
int count;

int main() {
    pthread_t threads[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++) {
        int res = pthread_create(&threads[i], NULL, thread_function, (void *)(intptr_t)i);
        if (res != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        int res = pthread_join(threads[i], NULL);
        if (res != 0) {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        } else {
            printf("Thread %d terminou\n", i);
        }
    }

    printf("Count: %d\n", count);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int id = (int)(intptr_t)arg; // Recupera o valor inteiro
    for (int j = 0; j < 10; j++) {
        count++;
    }
    printf("Thread %d completou\n", id);
    return NULL;
}
