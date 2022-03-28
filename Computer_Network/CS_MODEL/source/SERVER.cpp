#include <pthread.h>
#include <semaphore.h>
#include <stdio.h> // standard input and output library
#include <stdlib.h> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <errno.h> //It defines macros for reporting and retrieving error conditions through error codes
#include <time.h> //contains various functions for manipulating date and time
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

# define NUM_OF_SERVER_THREAD 5
# define MAXNUM_OF_CLIENT 20
# define MAX_DATA 500
# define EXE_TIME 30

pthread_mutex_t mutex;
int endflag = 0;
int welcome_sock = 0;

void* Server_thread(void* arg) {
    int answer_sock = 0;
    int id = *((int *)arg);
    while(true) {
        struct sockaddr_in Client_ADD;
        socklen_t Client_ADD_SIZE = sizeof(Client_ADD);

        //printf("\nHi,I am running server thread %d.Some Client hit me\n", id); // whenever a request from client came. It will be processed here.

        pthread_mutex_lock(&mutex);
        answer_sock = accept(welcome_sock, (struct sockaddr*)&Client_ADD, &Client_ADD_SIZE);
        printf("\nHi,I am running server thread %d.Some Client hit me\n", id);
        pthread_mutex_unlock(&mutex);
        char datasending[MAX_DATA] = {0};
        FILE *file_fp = fopen("data.txt", "rb");
        if(file_fp == NULL) {
            printf("Cannot open file!\n");
            close(answer_sock);
            pthread_exit(0);
        }

        //in_port_t client_port = Client_ADD.sin_port;
        //int port = client_port;
        //sprintf(datasending, "I am server thread %d, and I will send a file to a client with port ID of %d. The file is %s", id, port, file);
        //printf("\nserver %d, with data %s , the length is %ld\n", id, datasending, strlen(datasending));

        int n = 0;
        while((n = fread(datasending, 1, MAX_DATA, file_fp)) > 0) {
            if(write(answer_sock, datasending, n) < 0) {
                printf("\nThe connect is shutdown! Cannot write!");
                pthread_exit(0);
            }
        }
        shutdown(answer_sock, SHUT_WR);
        fclose(file_fp);
        
        /*
        if((n = write(answer_sock, datasending, strlen(datasending))) == -1) {
            printf("\nThe connect is shutdown! Cannot write!");
            pthread_exit(0);
        }
        */

        close(answer_sock);
        sleep(1);
        //pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main() {
    struct sockaddr_in Server_ADDR;

    pthread_mutex_init(&mutex, NULL);

    welcome_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&Server_ADDR, '0', sizeof(Server_ADDR));
    Server_ADDR.sin_family = AF_INET;
    Server_ADDR.sin_addr.s_addr = htonl(INADDR_ANY);
    Server_ADDR.sin_port = htons(2680);

    bind(welcome_sock, (struct sockaddr*)&Server_ADDR, sizeof(Server_ADDR));
    listen(welcome_sock, MAXNUM_OF_CLIENT);

    pthread_t servers[NUM_OF_SERVER_THREAD];
    int index_s[NUM_OF_SERVER_THREAD];

    for(int i = 0; i < NUM_OF_SERVER_THREAD; ++i) {
        index_s[i] = i;
        pthread_create(&servers[i], NULL, &Server_thread, (void*)&(index_s[i]));
    }

    for (int i = 0; i < NUM_OF_SERVER_THREAD; ++ i) {
        pthread_join(servers[i], NULL);
        printf("\nServer thread %d haved joint!\n", i);
	}

    return 0;
}