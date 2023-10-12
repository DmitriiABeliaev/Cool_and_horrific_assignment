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

int main(int argc, char *argv[]) {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    // create and bind to the socket
    int socketDescriptor = socket(PF_INET, SOCK_DGRAM);
    bind(socketDescriptor, (struct sockaddr*)&sin, sizeof(sin));

}

// using get getaddrinfo()
void foo() {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
}