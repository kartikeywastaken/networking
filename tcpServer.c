#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    int serverPort = 8080; // Echo port
    char msg_sent[2048] = "Okay this works";
    char msg_received[2048];

    int socket_fd = socket(AF_INET, SOCK_STREAM, 6);
    printf("Socket Created Successfully. The description is %d", socket_fd);
    if (socket_fd == -1)
    {
        perror("Socket creation failed"); // also tells you why it failed
        printf("Socket creation failed");
        exit(1);
    }

    struct sockaddr_in s; //sockaddr_in is predefined no need to redefine it
    struct sockaddr_in c;
    socklen_t server_addr_len = sizeof(s);
    socklen_t client_addr_len = sizeof(c);

    memset(&s, 0, sizeof(s));
    s.sin_family = AF_INET;
    s.sin_port = htons(serverPort); // htons is host to network short
    s.sin_addr.s_addr = INADDR_ANY;

    bind(socket_fd, (struct sockaddr*)&s, sizeof(struct sockaddr_in));
    listen(socket_fd, 10);
    while (1)
    {
        int newsock_fd = accept(socket_fd, (struct sockaddr*)&c, &client_addr_len);

        if (newsock_fd > 0)
        {
            printf("\n New socket created: %d", newsock_fd);
        }
    

         while (1)
        {
           read(newsock_fd, msg_received, sizeof(msg_received));
           write(newsock_fd, msg_sent, strlen(msg_sent));
        }
        close(newsock_fd);
    }
    close(socket_fd);
    

    return 0;
    
}