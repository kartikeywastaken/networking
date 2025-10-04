#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int socket(int domain, int type, int protocol){
    domain = AF_INET;
    type = SOCK_DGRAM; // Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
    protocol = 0;
}
