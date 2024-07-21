#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define SERVER_IP "10.12.1.2"
#define SERVER_PORT 12122

void *receive_messages(void *socket_desc);

int main() 
{
    int sock;
    struct sockaddr_in server;
    char message[1000];
    pthread_t recv_thread;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) 
    {
        printf("ERROR: %s\n", strerror(errno));
        return 1;
    }
    printf("CLIENT SOCKET CREATED\n");

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) 
    {
        printf("ERROR: %s\n", strerror(errno));
        return 1;
    }
    printf("CONNECTED TO SERVER\n");

    // Create thread to receive messages from server
    if (pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock) < 0) 
    {
        printf("ERROR: Could not create thread\n");
        return 1;
    }

    // Keep sending messages to server
    while (1) 
    {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';  // Remove newline character

        if (send(sock, message, strlen(message), 0) < 0) 
        {
            printf("ERROR: %s\n", strerror(errno));
            return 1;
        }

        if (strcmp(message, "exit") == 0) 
        {
            printf("Connection closed by client\n");
            break;
        }
    }

    close(sock);
    pthread_cancel(recv_thread); // Cancel the receive thread when done
    pthread_join(recv_thread, NULL); // Ensure the receive thread has finished
    return 0;
}

void *receive_messages(void *socket_desc) 
{
    int sock = *(int *)socket_desc;
    char message[1000];
    int message_length;

    while ((message_length = recv(sock, message, sizeof(message) - 1, 0)) > 0) 
    {
        message[message_length] = '\0';
        printf("Received message: %s\n", message);
    }

    if (message_length == 0) 
    {
        printf("Server disconnected\n");
    } 
    else if (message_length == -1) 
    {
        printf("ERROR: %s\n", strerror(errno));
    }

    return NULL;
}
