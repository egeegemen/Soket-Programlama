#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>


#define PORT 8181
#define BUFFER_SIZE 4000000 // 4 MB

void read_file(FILE *fp, int sockfd, char *filename) {
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

void send_file(char *ip, char *filename) {
    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket.");
        exit(1);
    }
    printf("Client socket created successfully.\n");

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

    read_file(fp, sockfd, filename);
    printf("File data sent successfully.\n");

    fclose(fp);
    close(sockfd);
    printf("Disconnected from server.\n");
}

void write_file(int new_sock) {
    int n;
    FILE *fp;
    char filename[100];
    char buffer[BUFFER_SIZE];
    int total_bytes = 0;  // Toplam alınan byte miktarı
    
    memset(filename, 0, 100); // Dosya adı için belleği temizleyin
    recv(new_sock, filename, 100, 0);
    filename[strcspn(filename, "\n")] = 0;  // Dosya adının sonundaki yeni satır karakterini kaldırın
    recv(new_sock, buffer, 1, 0);  // Dosya adının alınmasını beklemek için 1 byte alın
    printf("File name: %s\n", filename);

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error in creating file.");
        exit(1);
    }

     while ((n = recv(new_sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, sizeof(char), n, fp);
        total_bytes += n;
        printf("Received %.2f bytes, Total: %.2f MB\n", n / (1024.0 * 1024.0), total_bytes / (1024.0 * 1024.0));  // Byte'dan MB'ye çevirme
        memset(buffer, 0, BUFFER_SIZE);
    }
    fclose(fp);
}

void receive_file(char *ip) {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket.");
        exit(1);
    }
    printf("Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in bind.");
        exit(1);
    }
    printf("Bind to port %d\n", PORT);

    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Error in listening.");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    if (new_sock < 0) {
        perror("Error in accept.");
        exit(1);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));

    write_file(new_sock);
    printf("File received and saved successfully.\n");

    close(new_sock);
    close(sockfd);
}

int main(int ac, char *av[]) {
    if (ac >= 2 && ac <= 4) {
        if (!strcmp(av[1], "send"))
            send_file(av[2], av[3]);
        else if (!strcmp(av[1], "receive"))
            receive_file(av[2]);
        else {
            printf("Invalid command.\n");
            printf("Usage1: %s send <ip> <filename>\n", av[0]);
            printf("Usage2: %s receive <ip>\n", av[0]);
            exit(1);
        }
    } else {
        printf("Invalid number of arguments.\n");
        printf("Usage1: %s send <ip> <filename>\n", av[0]);
        printf("Usage2: %s receive\n", av[0]);
        exit(1);
    }
}