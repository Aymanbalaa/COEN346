#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct __barrier_t {
    int count;            // count of threads that have reached the barrier
    int num_threads;      // total number of threads
    sem_t mutex;           // protects access to the barrier
    sem_t barrier_sem;     // used for blocking threads until the barrier is reached
} barrier_t;

// the single barrier we are using for this program
barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {
    b->count = 0;
    b->num_threads = num_threads;
    sem_init(&b->mutex, 0, 1);
    sem_init(&b->barrier_sem, 0, 0);
}

void barrier(barrier_t *b) {
    sem_wait(&b->mutex);
    b->count++;
    sem_post(&b->mutex);

    if (b->count == b->num_threads) {
        // Last thread to reach the barrier
        for (int i = 0; i < b->num_threads - 1; i++) {
            sem_post(&b->barrier_sem);
        }
    }

    sem_wait(&b->barrier_sem);  // Block until all threads reach the barrier

    sem_wait(&b->mutex);
    b->count--;
    sem_post(&b->mutex);

    if (b->count == 0) {
        // Last thread to leave the barrier
        for (int i = 0; i < b->num_threads - 1; i++) {
            sem_post(&b->barrier_sem);
        }
    }

    sem_wait(&b->barrier_sem);  // Block until all threads leave the barrier
}

// XXX: don't change below here (just run it!)
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *)arg;
    printf("child %d: before\n", t->thread_id);
    barrier(&b);
    printf("child %d: after\n", t->thread_id);
    return NULL;
}

// run with a single argument indicating the number of 
// threads you wish to create (1 or more)
int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);
    
    int i;
    for (i = 0; i < num_threads; i++) {
        t[i].thread_id = i;
        pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++) 
        pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}
