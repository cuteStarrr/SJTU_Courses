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

# define MAXNUM_OF_CLIENT 15
# define MAX_DATA 500

void* Client(void* arg) {
    int id = *((int *)arg);
    char filename[50] = {0};
    sprintf(filename, "data%d.txt", id);
    FILE * fp = fopen(filename, "wb");
    if(fp == NULL){
        printf("Cannot open file!\n");
        pthread_exit(0);
    }

    char datareceived[MAX_DATA];
    memset(datareceived, '0', sizeof(datareceived));
    
    int Client_sock = 0;
    if((Client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))< 0)
    {
        printf("\nClient socket %d not created \n", id);
        pthread_exit(0);
    }
    //else {printf("\nClient socket %d created \n", id);}

    struct sockaddr_in Client_ADD;
    socklen_t Client_ADD_SIZE = sizeof(Client_ADD);

    struct sockaddr_in Server_ADDR;
    memset(&Server_ADDR, '0', sizeof(Server_ADDR));
    Server_ADDR.sin_family = AF_INET;
    Server_ADDR.sin_addr.s_addr = inet_addr("127.0.0.1");
    Server_ADDR.sin_port = htons(2680);

    if(connect(Client_sock, (struct sockaddr*)& Server_ADDR, sizeof(Server_ADDR))) {
        printf("\nConnection failed due to port and ip problems\n");
        pthread_exit(0);
    }

    getsockname(Client_sock, (struct sockaddr*)&Client_ADD, &Client_ADD_SIZE);
    in_port_t client_port = Client_ADD.sin_port;
    int port = client_port;
    
    int n = 0;
    while((n = read(Client_sock, datareceived, sizeof(datareceived) - 1)) > 0) {
        fwrite(datareceived, n, 1, fp);
    }
    printf("File transfer succeed!");

    fclose(fp);
    close(Client_sock);

    /*
    if((n = read(Client_sock, datareceived, sizeof(datareceived) - 1)) == -1) {
        printf("\nReceive error! The connect may be shutdown!\n");
        pthread_exit(0);
    }
    else {datareceived[n] = 0; printf("\nI am client %d with port number of %d, and I have received the file, the bit of the file is %d \n, the file is as follows: \n %s", id, port, n, datareceived);}
    */

    pthread_exit(0);
}

int main() {
    pthread_t clients[MAXNUM_OF_CLIENT];
    int index_c[MAXNUM_OF_CLIENT];

    for(int j = 0; j < MAXNUM_OF_CLIENT; ++j) {
        index_c[j] = j;
        pthread_create(&clients[j], NULL, &Client, (void*)&(index_c[j]));
    }

    for (int j = 0; j < MAXNUM_OF_CLIENT; ++ j) {
        pthread_join(clients[j], NULL);	
        printf("\n @ Client thread %d haved joint! @ \n", j);
	}

    return 0;
}