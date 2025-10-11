#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){

     int number;
     char buffer[1024];

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 17);
    if (socket_fd == -1)
    {
        perror("Socket creation failed"); // also tells you why it failed
        printf("Socket creation failed");
        exit(1);
    }

    printf("Socket Created Successfully. The description is %d", socket_fd);
    int serverPort = 7; // Echo port

    struct sockaddr_in s; //sockaddr_in is predefined no need to redefine it 
    struct sockaddr_in c;

    memset(&s, 0, sizeof(s));
    s.sin_family = AF_INET;
    s.sin_port = htons(serverPort);
    s.sin_addr.s_addr = INADDR_ANY;


    bind(socket_fd, (struct sockaddr*)&s, sizeof(struct sockaddr_in));
    // Declare a variable to hold the size of the client address structure
    socklen_t client_addr_len = sizeof(c); // size of client addr
        // if (canR > 0)
        // {
        //     printf("Server is up and running!\n");
        //     printf("%s", buffer);
        // } else {
        //     perror("Unable to listen\n");
        //     exit(1);
        // }  
    while (1)
    {  
     int canR = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&c, &client_addr_len); // passing the memory address
     number = atoi(buffer);
     printf("number received : %d\n", number);
     sprintf(buffer, "%d\n", number*2);
     sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&c, sizeof(struct sockaddr_in));

     sleep(5);
          }
        
    return 0;
}