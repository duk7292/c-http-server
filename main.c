#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    struct sockaddr_in my_addr; 

    int sfd; 

    if((sfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("socket return: %d , could not create socket\n",sfd);
        exit(EXIT_FAILURE);
    }
    

    my_addr.sin_family = AF_INET; // match the socket() call

    my_addr.sin_port = htons(5100); // specify port to listen on

    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); //allow the server to accept a client connection on any interface

    if( bind(sfd, (struct sockaddr *) &my_addr, sizeof(my_addr))<0)
    {
        printf("could not bind socket\n");
        exit(EXIT_FAILURE);
    }

    if (listen(sfd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1) 
    {
        struct sockaddr client_addr; 

        int client_addr_size = sizeof(client_addr);

        int new_socket;
        
        if((new_socket = accept(sfd, &client_addr, &client_addr_size))<0)
        {
            printf("socket return: %d , could not create socket\n",new_socket);
            exit(EXIT_FAILURE);
        }


        char buffer[1024] = {0}; 

        int bytes_received = recv(new_socket, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received > 0) {

            printf("Received: %s", buffer);
        } else if (bytes_received == 0) {
            printf("Client disconnected.\n");
        } else {
            perror("recv");
        }
        char send_buffer[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, world!";
        send(new_socket, send_buffer, strlen(send_buffer), 0);

        close(new_socket);
    }


    return 1;
}