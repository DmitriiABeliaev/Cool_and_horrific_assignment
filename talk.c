#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
// Networking includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
// My own files includes
#include "list.h"

// CSIL MACHINE IP: 127.0.0.1
#define PORT 6969
#define MAX_LEN 1024

#define _GNU_SOURSE

// using get getaddrinfo()
void foo() {
    //struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
}

//main(int argc, char *argv[])
int main() {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    // create and bind to the socket
    int socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    bind(socketDescriptor, (struct sockaddr*)&sin, sizeof(sin));

    while(1){
    //receive data
    struct sockaddr_in sinRemote;
    unsigned int sin_len = sizeof(sinRemote);
    char messageRx[MAX_LEN];
    int bytesRx = recvfrom(socketDescriptor,
                    messageRx, MAX_LEN, 0,
                    (struct sockaddr*) &sinRemote, &sin_len);
    
    int terminateIdx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN -1;
    messageRx[terminateIdx] = 0;
    printf("Message received (%d byttes): '%s'\n", bytesRx, messageRx);

    //create reply
    char messageTx[MAX_LEN];
    sprintf(messageRx, "Hello world%d\n", 42);

    //send reply
    sin_len = sizeof(sinRemote);
    sendto(socketDescriptor, messageTx, strlen(messageTx), 0, 
            (struct sockaddr*) &sinRemote, sin_len);

    }
    //close socket
    close(socketDescriptor);
}