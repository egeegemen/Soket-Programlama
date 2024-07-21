#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 4000000 // 4 MB

void send_file(FILE *fp, int sockfd, char *filename) {
    char buffer[BUFFER_SIZE] = {0};
    int n;
    int total_bytes = 0;

    send(sockfd, filename, strlen(filename), 0);
    send(sockfd, "\n", 1, 0);
    while ((n = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0) {
        if (send(sockfd, buffer, n, 0) == -1) {
            perror("Error in sending file.");
            exit(1);
        }
        total_bytes += n;
        printf("Gönderilen %.2f / Toplam MB: %.2f MB\n", n / (1024.0 * 1024.0), total_bytes / (1024.0 * 1024.0));
        memset(buffer, 0, BUFFER_SIZE);
    }
}

int main(int ac, char *av[]) {
    char *ip = "10.12.2.6";
    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = av[1];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket.");
        exit(1);
    }
    printf("Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in connecting.");
        exit(1);
    }
    printf("Connected to Server.\n");

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error in reading file.");
        exit(1);
    }

    send_file(fp, sockfd, filename);
    printf("File data sent successfully.\n");

    fclose(fp);
    close(sockfd);
    printf("Disconnected from server.\n");

    return 0;
}
