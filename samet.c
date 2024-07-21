#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

int main() 
{
    int server_socket, client_socket, max_sd, activity, new_socket, sd;
    int client_sockets[30], max_clients = 30;
    struct sockaddr_in server, client;
    char buffer[1025];  // data buffer of 1K
    fd_set readfds;     // set of socket descriptors

    // Initialize all client_sockets to 0 so not checked
    for (int i = 0; i < max_clients; i++) 
        client_sockets[i] = 0;

    // Step 1: Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_socket == -1)
    {
        printf("ERROR: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("SERVER SOCKET CREATED\n");

    // Step 2: Define server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("10.12.1.2");
    server.sin_port = htons(12122);

    // Step 3: Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("ERROR: %s\n", strerror(errno));
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("BIND SUCCESSFUL\n");

    // Step 4: Listen for incoming connections
    if (listen(server_socket, 3) < 0)
    {
        printf("ERROR: %s\n", strerror(errno));
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("SUCCESSFUL | Port Listening Successful! Port: %d\n", ntohs(server.sin_port));

    int addrlen = sizeof(client);

    while(1) 
    {
        // Clear the socket set
        FD_ZERO(&readfds);

        // Add server_socket to set
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;

        // Add child sockets to set
        for (int i = 0; i < max_clients; i++) 
        {
            // Socket descriptor
            sd = client_sockets[i];
                
            // If valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);
                
            // Highest file descriptor number, need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }

        // Wait for an activity on one of the sockets, timeout is NULL so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) 
        {
            printf("ERROR: %s\n", strerror(errno));
        }

        // If something happened on the master socket, then it's an incoming connection
        if (FD_ISSET(server_socket, &readfds)) 
        {
            if ((new_socket = accept(server_socket, (struct sockaddr *)&client, (socklen_t*)&addrlen)) < 0) 
            {
                printf("ERROR: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            printf("New connection, socket fd is %d, ip is : %s, port: %d\n", new_socket, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            
            // Add new socket to array of sockets
            for (int i = 0; i < max_clients; i++) 
            {
                // If position is empty
                if (client_sockets[i] == 0) 
                {
                    client_sockets[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
        }

        // Else it's some IO operation on some other socket
        for (int i = 0; i < max_clients; i++) 
        {
            sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds)) 
            {
                // Check if it was for closing, and also read the incoming message
                int valread;
                if ((valread = read(sd, buffer, 1024)) == 0) 
                {
                    // Somebody disconnected, get his details and print
                    getpeername(sd, (struct sockaddr*)&client, (socklen_t*)&addrlen);
                    printf("Host disconnected, ip %s, port %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                        
                    // Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_sockets[i] = 0;
                } 
                else 
                {
                    // Set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                    printf("Received message from client: %s\n", buffer);

                    // Broadcast the message to all other clients
                    for (int j = 0; j < max_clients; j++) 
                    {
                        if (client_sockets[j] != 0 && client_sockets[j] != sd) 
                        {
                            send(client_sockets[j], buffer, strlen(buffer), 0);
                        }
                    }

                    if (strcmp(buffer, "exit") == 0) 
                    {
                        printf("Connection closed by client\n");
                        close(sd);
                        client_sockets[i] = 0;
                    } 
                    else 
                    {
                        printf("Message: %s\n", buffer);
                    }
                }
            }
        }
    }

    close(server_socket);
    return 0;
}
