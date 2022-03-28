/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include "threadpool.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

int endflag;

// this represents work that has to be 
// completed by a thread in the pool
typedef struct 
{
    void (*function)(void *p);
    void *data;
}task;

// the work queue
struct work_queue {
	task worktodo;
	struct work_queue *next;
} *head, *tail;

// the worker bee
pthread_t bee[NUMBER_OF_THREADS];

// the mutex lock
pthread_mutex_t in_queue,out_queue;

//semaphore
sem_t work_sem;

// insert a task into the queue
// returns 0 if successful or 1 otherwise, 
int enqueue(task t) 
{
    tail -> next = (struct work_queue *) malloc (sizeof(struct work_queue));
    
    if(tail -> next == NULL)
        return 1;

    tail = tail -> next;
    tail -> worktodo = t;
    tail -> next = NULL;
    return 0;
}

// remove a task from the queue
task dequeue() 
{
    if(head == tail) {
        fprintf(stderr, "No work to do!\n");
        exit(1);
    }
    else {
        struct work_queue *tmp;
        tmp = head;
        head = head -> next;
        free(tmp);
        return head -> worktodo;
    }
}

// the worker thread in the thread pool
void *worker(void *param)
{
    static task nextwork;

    while(TRUE) {
        if (endflag)
            break;

		sem_wait(&work_sem); // the number of work should >0 to execute
		
		pthread_mutex_lock(&out_queue);
		nextwork = dequeue();
		pthread_mutex_unlock(&out_queue);

		// execute the task
		execute(nextwork.function, nextwork.data);
	}

    pthread_exit(0);
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*somefunction)(void *p), void *p)
{
    (*somefunction)(p);
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *p), void *p)
{
    static task worktodo;
    worktodo.function = somefunction;
    worktodo.data = p;

    pthread_mutex_lock(&in_queue);
	if(enqueue(worktodo) == 0)
        sem_post(&work_sem);
	pthread_mutex_unlock(&in_queue);

    return 0;
}

// initialize the thread pool
void pool_init(void)
{
    endflag = 0;

    head = (struct work_queue *) malloc (sizeof(struct work_queue));
	if (head == NULL) {
		fprintf(stderr, "Allocation for work queue fails!\n");
		exit(1);
	}
	head -> next = NULL;
	tail = head;

    // initialize the mutex and semaphore
    pthread_mutex_init(&in_queue, NULL);
    pthread_mutex_init(&out_queue, NULL);
    sem_init(&work_sem, 0, 0);

    for(int i = 0; i < NUMBER_OF_THREADS; ++i) {
        pthread_create(&bee[i],NULL,worker,NULL);
    }

}

// shutdown the thread pool
void pool_shutdown(void)
{
    endflag = 1;

    // should release semaphore before join the thread
    sem_post(&work_sem);
    for(int i = 0; i < NUMBER_OF_THREADS; ++i) {
        pthread_join(bee[i],NULL);
    }

    pthread_mutex_destroy(&in_queue);
    pthread_mutex_destroy(&out_queue);
    sem_destroy(&work_sem);
}