#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>

int main ()
{
    //1.Adim: Socket olusturulmasi
    int sckt;
    sckt = socket(AF_INET, SOCK_STREAM, 0);
    if (sckt == -1)
        printf("ERROR: %s\n", strerror(errno));
    else
        printf("CLIENT SOCKET CREATED\n");
    

    //2.Adim: Serverin adres bilgilerinin belirlenmesi
    struct sockaddr_in myclient;
    myclient.sin_family = AF_INET;
    myclient.sin_addr.s_addr = inet_addr("127.0.0.1");
    myclient.sin_port = htons(12345);


    //3.Adim: Servera baglanma
    int cnct;
    cnct = connect(sckt, (struct sockaddr *)&myclient, sizeof(myclient));
    if (cnct == -1)
        printf("ERROR: %s\n", strerror(errno));
    else
        printf("SUCCESSFUL | Connection Established\n");

    
    //4.Adim: Mesaj gonderme
    char msg_client[] = "Hello from client!";
    int msg_size;
    msg_size = send(sckt, msg_client, strlen(msg_client), 0);
    if (msg_size == -1)
        printf("ERROR: %s\n", strerror(errno));
    else
        printf("SUCCESSFUL | Message Sent\n");
}