#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main() 
{
    //1.Adim: Socket olusturulmasi
    int sckt;
    sckt = socket(AF_INET, SOCK_STREAM, 0); // AF_inet: IPv4, SOCK_STREAM: TCP: Bagalanti noktasi olusturduk.

    if (sckt == -1)
        printf("ERROR: %s\n" , strerror(errno));
    else 
        printf("SERVER SOCKET CREATED\n");
    

    //2.Adim: Serverin adres bilgilerinin belirlenmesi
    struct sockaddr_in myserver;
    myserver.sin_family = AF_INET; // IPv4
    myserver.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP Adresi
    myserver.sin_port = htons(17345); // Port numarasi; htons fonksiyonu ile port numarasi network byte ordera cevirilir.


    //3.Adim: Socketin adres bilgileri ile baglanmasi
    int bnd;
    bnd = bind(sckt, (struct sockaddr *)&myserver, sizeof(myserver));

    
    if (bnd == -1)
        printf("ERROR: %s\n" , strerror(errno));
    else 
        printf("BIND SUCCESSFUL\n");


    //4.Adim: Baglanti isteklerinin dinlenmesi
    int lstn;
    lstn = listen(sckt, 5); // 5: Maximum baglanti sayisi

    if (lstn == -1)
        printf("ERROR: %s\n" , strerror(errno));
    else 
        printf("SUCCESSFUL | Port Listening Successful! Port: %d\n", ntohs(myserver.sin_port)); // nthons: Bu fonksiyon ile port numarasi network byte orderdan host byte ordera cevirilir.


    //5.Adim: Baglanti kabul etme
    struct sockaddr_in client; // Clientin adres bilgilerini serverda tutmak icin olusturuldu.
    unsigned int client_size = sizeof(client);
        
    int clnt_accept;
    clnt_accept = accept(sckt, (struct sockaddr *)&client, &client_size);

    if (clnt_accept == -1)
        printf("ERROR: %s\n" , strerror(errno));
    else
    {
        printf("------Waiting for connection...\n");
        sleep(1);
        printf("SUCCESSFUL | Connection Accepted\n");
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN); // inet_ntop: IP adresini network byte orderdan host byte ordera cevirir.
        printf("Connected to client: %s:%d\n", client_ip, ntohs(client.sin_port)); // ntohs: Port numarasi network byte orderdan host byte ordera cevirir.
    }

    //6.Adim: Mesaj alma
    while (1) // Surekli mesaj almak icin sonsuz dongu
    {
        char msg[100];
        int msg_size;
        msg_size = recv(clnt_accept, msg, 100, 0); // 100: Mesajin boyutu

        if (msg_size == -1)
            printf("ERROR: %s\n" , strerror(errno));
        else
        {
            printf("------Waiting for message...\n");
            sleep(2); 
            printf("SUCCESSFUL | Message Received: %s\n", msg);
        }

        if (strcmp(msg, "exit") == 0) 
        {
            printf("Bağlantı kapatılıyor...\n");
            break;
        }
        memset(msg, 0, sizeof(msg)); // Mesajin icerigini sifirla
    }

    //7.Adim: Baglanti sonlandirma
    close(clnt_accept);
    close(sckt);
}
