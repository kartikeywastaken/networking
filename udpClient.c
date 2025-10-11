#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    const char* serverName = "127.0.0.1"; // Example IP also a pointer to char
    int serverPort = 7; // Echo port
    int num = 2;
    char msg[2048];
    char buffer[2048];

    struct sockaddr_in c; //sockaddr_in is predefined no need to redefine it 
    struct sockaddr_in s;

    socklen_t server_addr_len = sizeof(s);

    memset(&c, 0, sizeof(c));
    c.sin_family = AF_INET;
    c.sin_port = htons(serverPort); // htons is host to network short
    inet_aton(serverName, &c.sin_addr); // internet address to network address <-- inet_aton

    // It's crucial to check the return value of this function
    // if (inet_aton(serverName, &s.sin_addr) == 0) {
    //     fprintf(stderr, "Invalid address\n");
    //     exit(1);
    // }
 
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 17);
    if (socket_fd == -1)
    {
        perror("Socket creation failed");
        exit(1);
    }

    printf("Socket Created Successfully. The descriptor is %d\n", socket_fd);
    sprintf(msg, "%d\n", num );

    // sending data
    int sendP = sendto(socket_fd, msg, strlen(msg), 0, (struct sockaddr *)&c, sizeof(struct sockaddr_in));
    if (sendP > 0)
        {
            printf("\nPackets were sent out");
        } else {
            perror("Couldnt sent packets");
        }

    while (1)
    {
        recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&s, &server_addr_len);
        int back_num = atoi(buffer);
        printf("number received: %d\n", back_num);
        sprintf(msg, "%d\n", back_num*2 );
        sendto(socket_fd, msg, strlen(msg), 0, (struct sockaddr *)&s, sizeof(struct sockaddr_in));

        sleep(5);
    }

    return 0;
}