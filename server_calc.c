#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size = sizeof(clientAddr);
    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }

    printf("UDP Calculator Server running on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &addr_size);

        printf("Received: %s\n", buffer);

        char func[10];
        double angle, result = 0.0;
        sscanf(buffer, "%s %lf", func, &angle);

        // Convert degrees to radians
        double rad = angle * M_PI / 180.0;

        if (strcmp(func, "sin") == 0) result = sin(rad);
        else if (strcmp(func, "cos") == 0) result = cos(rad);
        else if (strcmp(func, "tan") == 0) result = tan(rad);
        else {
            snprintf(buffer, BUFFER_SIZE, "Invalid function");
            sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&clientAddr, addr_size);
            continue;
        }

        snprintf(buffer, BUFFER_SIZE, "Result: %.4f", result);
        sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&clientAddr, addr_size);
    }

    close(sockfd);
    return 0;
}
