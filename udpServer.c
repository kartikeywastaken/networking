#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Using 0 for the protocol is more standard and portable
int create_socket(){
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    return socket_fd;
}

int main(){
    const char* serverName = "127.0.0.1"; // Example IP
    int serverPort = 7; // Echo port

    struct sockaddr_in s; //sockaddr_in is predefined no need to redefine it 

    memset(&s, 0, sizeof(s));
    s.sin_family = AF_INET;
    s.sin_port = htons(serverPort);
    inet_aton(serverName, &s.sin_addr);

    // It's crucial to check the return value of this function
    // if (inet_aton(serverName, &s.sin_addr) == 0) {
    //     fprintf(stderr, "Invalid address\n");
    //     exit(1);
    // }
 
    int socket_fd = create_socket();
    if (socket_fd == -1)
    {
        perror("Socket creation failed");
        exit(1);
    }

    printf("Socket Created Successfully. The descriptor is %d\n", socket_fd);

    // sending data
    char msg[] = "oi its up fellas";
    sendto(socket_fd, msg, strlen(msg), 0, (struct sockaddr *)&s, sizeof(struct sockaddr_in));

    return 0;
}