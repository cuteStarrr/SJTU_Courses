# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include "buffer.h"

# define TRUE 1

// semaphore empty, full
sem_t empty, full;
// mutex lock mutex
pthread_mutex_t mutex;
// terminate flag
int endflag;

// producer thread
void *producer(void *param) {
	buffer_item item;
	
	while(TRUE) {
		int time_period;
		time_period = rand() % 3;
		sleep(time_period);

        if (endflag) break;
		
		// produce an item
		item = rand();

		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		
		if (insert_item(item)) {
			fprintf(stderr, "Can not insert an item!\n");
			exit(1);
		}
        else fprintf(stdout, "Producer produces an item %d.\n", item);

		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
    // exit to release mutex
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

// consumer thread
void *consumer(void *param) {
	buffer_item item;
	
	while(TRUE) {
		int time_period;
		time_period = rand() % 3;
		sleep(time_period);

        if (endflag) break;

		// consume an item
        sem_wait(&full);
		pthread_mutex_lock(&mutex);

		if (remove_item(&item)) {
			fprintf(stderr, "Can not consume an item!\n");
			exit(1);
		}
        else fprintf(stdout, "Consumer consumes an item %d.\n", item);
        // exit to release mutex
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	pthread_t *producers, *consumers;
	int exe_time, producer_number, consumer_number;

	// get command line arguments
	exe_time = atoi(argv[1]);
	producer_number = atoi(argv[2]);
	consumer_number = atoi(argv[3]);

	// initialize buffer
	buffer_initialization();
	endflag = 0;

	// create the mutex lock
	pthread_mutex_init(&mutex, NULL);

	// create the semaphore
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);

	// create threads
	producers = (pthread_t *) malloc (sizeof(pthread_t) * producer_number);
	consumers = (pthread_t *) malloc (sizeof(pthread_t) * consumer_number);

	for(int i = 0; i < producer_number; ++ i)
		pthread_create(&producers[i], NULL, &producer, NULL);
	for(int i = 0; i < consumer_number; ++ i)
		pthread_create(&consumers[i], NULL, &consumer, NULL);

	// sleep
	sleep(exe_time);

	// exit
	endflag = 1;

	sem_post(&empty);
	sem_post(&full);

	for (int i = 0; i < producer_number; ++ i) {
        pthread_join(producers[i], NULL);
	}
	for (int i = 0; i < consumer_number; ++ i) {
        pthread_join(consumers[i], NULL);		
	}
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	
	free(producers);
	free(consumers);

	return 0;
}
