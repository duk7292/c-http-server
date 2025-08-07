#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    
    //create socket
    int listen_sock; 
    if((listen_sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("socket return: %d , could not create socket\n",listen_sock);
        exit(EXIT_FAILURE);
    }
    

    //bind scocket to ip and port
    struct sockaddr_in my_addr; 

    my_addr.sin_family = AF_INET; 
    my_addr.sin_port = htons(5100); 
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if( bind(listen_sock, (struct sockaddr *) &my_addr, sizeof(my_addr))<0)
    {
        printf("could not bind socket\n");
        exit(EXIT_FAILURE);
    }

    //make socket listen

    if (listen(listen_sock, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //
    while(1) 
    {
        struct sockaddr client_addr; 

        int client_addr_size = sizeof(client_addr);

        int conn_sock;
        
        //wait for request and create new socket 
        if((conn_sock = accept(listen_sock, &client_addr, &client_addr_size))<0)
        {
            printf("socket return: %d , could not create socket\n",conn_sock);
            exit(EXIT_FAILURE);
        }

        //handle request
        char buffer[1024] = {0}; 

        int bytes_received = recv(conn_sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received > 0) {

            printf("Received: %s", buffer);
        } else if (bytes_received == 0) {
            printf("Client disconnected.\n");
        } else {
            perror("recv");
        }

        //send response
        char send_buffer[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, world!";
        send(conn_sock, send_buffer, strlen(send_buffer), 0);

        close(conn_sock);
    }


    return 1;
}