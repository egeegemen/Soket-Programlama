#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>


#define PORT 8080
#define BUFFER_SIZE 4000 // 4 MB

void send_file(char *ip, char *filename) {
    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char buffer[BUFFER_SIZE] = {0};
    int n;
    int total_bytes = 0;

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

    send(sockfd, filename, strlen(filename), 0);
    send(sockfd, "\n", 1, 0);
    while ((n = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0) {
        if (send(sockfd, buffer, n, 0) == -1) {
            perror("Error in sending file.");
            exit(1);
        }
        total_bytes += n;
        printf("Sent %.2f / Total MB: %.2f MB\n", n / (1024.0 * 1024.0), total_bytes / (1024.0 * 1024.0));
        memset(buffer, 0, BUFFER_SIZE);
    }
    printf("File data sent successfully.\n");
}

void receive_file() {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;
    char filename[100];
    int total_bytes = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket.");
        exit(1);
    }
    printf("Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in bind.");
        exit(1);
    }
    printf("Bind to port %d\n", PORT);

    if (listen(sockfd, 10) == 0) {
        printf("Listening....\n");
    } else {
        perror("Error in listening.");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

    fp = fopen("received.txt", "wb");
    if (fp == NULL) {
        perror("Error in creating file.");
        exit(1);
    }

    memset(filename, 0, 100);
    recv(new_sock, filename, 100, 0);
    filename[strcspn(filename, "\n")] = 0;
    recv(new_sock, buffer, 1, 0);
    printf("File name: %s\n", filename);

    while ((n = recv(new_sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, sizeof(char), n, fp);
        total_bytes += n;
        printf("Received %.2f bytes, Total: %.2f MB\n", n / (1024.0 * 1024.0), total_bytes / (1024.0 * 1024.0));
        memset(buffer, 0, BUFFER_SIZE);
    }
    printf("File data received successfully.\n");
    fclose(fp);
}

int main(int ac, char *av[]) {
    if (ac <= 2 && ac >= 4) {
        printf("Usage1: %s send <ip> <filename>\n", av[0]);
        printf("Usage2: %s receive\n", av[0]);
        exit(1);
    }
    if (strcmp(av[1], "send"))
        send_file(av[2], av[3]);
    else if (strcmp(av[1], "receive"))
        receive_file();
    else {
        printf("Invalid command.\n");
        printf("Usage1: %s send <ip> <filename>\n", av[0]);
        printf("Usage2: %s receive\n", av[0]);
        exit(1);
    }
}