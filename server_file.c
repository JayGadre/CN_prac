#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    FILE *fp;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
    }
    printf("Client connected. Receiving file...\n");

    // Open file for writing
    fp = fopen("received_file.txt", "wb");
    if (!fp) {
        perror("File open");
        exit(EXIT_FAILURE);
    }

    // Receive data
    ssize_t bytes;
    while ((bytes = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, 1, bytes, fp);
    }

    printf("File received successfully.\n");

    fclose(fp);
    close(new_socket);
    close(server_fd);

    return 0;
}
