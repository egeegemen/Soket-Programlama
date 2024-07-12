#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

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
    myclient.sin_port = htons(16345);


    //3.Adim: Servera baglanma
    int cnct;
    cnct = connect(sckt, (struct sockaddr *)&myclient, sizeof(myclient));
    if (cnct == -1)
        printf("ERROR: %s\n", strerror(errno));
    else
    {
        sleep(4);
        printf("SUCCESSFUL | Connection Established\n");
    }

    
    // 4. Adım: Mesaj gönderme
    int msg_size;
    char msg_client[100];

    while (1) 
    {
        printf("Lütfen gönderilecek mesajı girin (çıkış için 'exit' yazın): ");
        
        if (fgets(msg_client, sizeof(msg_client), stdin) != NULL) 
        {
            // Sonundaki newline karakterini kaldır
            size_t len = strlen(msg_client);
            if (len > 0 && msg_client[len-1] == '\n') {
                msg_client[len-1] = '\0';
            }

            msg_size = send(sckt, msg_client, strlen(msg_client), 0);

            if (msg_size == -1)
                printf("ERROR: %s\n", strerror(errno));
            else
                printf("SUCCESSFUL | Message Sent\n");
            
            // Çıkış komutu kontrolü
            if (strcmp(msg_client, "exit") == 0) {
                printf("Bağlantı kapatılıyor...\n");
                break;
            }
        }
    }
}
