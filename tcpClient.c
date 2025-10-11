#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    const char* serverName = "127.0.0.1"; // Example IP also a pointer to char
    int serverPort = 8080; // Echo port
    char msg_sent[2048] = "Okay this works";
    char msg_received[2048];

    struct sockaddr_in c; //sockaddr_in is predefined no need to redefine it
    socklen_t server_addr_len = sizeof(c);

    memset(&c, 0, sizeof(c));
    c.sin_family = AF_INET;
    c.sin_port = htons(serverPort); // htons is host to network short
    inet_aton(serverName, &c.sin_addr); // internet address to network address <-- inet_aton

    int socket_fd = socket(AF_INET, SOCK_STREAM, 6);

    int con = connect(socket_fd, (struct sockaddr*)&c, server_addr_len);
    if (con == -1)
    {
        perror("Error: ");
    }
    while (1)
    {
        write(socket_fd, msg_sent, sizeof(struct sockaddr_in));
        read(socket_fd, msg_received, sizeof(struct sockaddr_in));
        sleep(5);
    }

    return 0;
    
}