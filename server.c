#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd,new_socket;
    struct sockaddr_in addr;
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET,SOCK_STREAM,0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd,(struct sockaddr *)&addr,sizeof(addr));

    listen(server_fd,1);

    new_socket = accept(server_fd,NULL,NULL);

    read(new_socket,buffer,sizeof(buffer));

    printf("Client : %s",buffer);

    send(new_socket,"Hello from server",17,0);
    close(new_socket);
    close(server_fd);
}