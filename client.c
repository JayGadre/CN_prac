#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock;
    struct sockaddr_in serv;
    char buffer[1024] = {0};

    sock = socket(AF_INET,SOCK_STREAM,0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);

    connect(sock,(struct sockaddr*)&serv,sizeof(serv));

    send(sock,"Hello from client",17,0);

    read(sock,buffer,sizeof(buffer));
    printf("Server :%s",buffer);

    close(sock);
}