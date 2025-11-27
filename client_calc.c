#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE], func[10];
    double angle;
    struct sockaddr_in serverAddr;
    socklen_t addr_size = sizeof(serverAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    printf("Enter function (sin/cos/tan): ");
    scanf("%s", func);
    printf("Enter angle (degrees): ");
    scanf("%lf", &angle);

    snprintf(buffer, BUFFER_SIZE, "%s %lf", func, angle);

    sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&serverAddr, addr_size);

    recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&serverAddr, &addr_size);
    printf("Server: %s\n", buffer);

    close(sockfd);
    return 0;
}
