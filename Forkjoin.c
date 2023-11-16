#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;

void *child(void *arg) {
    printf("child\n");
    // Signal parent that child has completed
    sem_post(&s);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    
    // Initialize semaphore with initial value 0
    sem_init(&s, 0, 0);

    // Create child thread
    pthread_create(&p, NULL, child, NULL);

    // Wait for the child to complete using semaphore
    sem_wait(&s);

    // Destroy the semaphore
    sem_destroy(&s);

    printf("parent: end\n");
    return 0;
}

