# Soket-Programlama

Yazdığım program cok basit anlamda soket programlamaya bir örnektir. Alt tarafta bilinmesi gereken bilgileri yazdım.

- **Soket Programlama Nedir?**
  Soket programlama, bilgisayar ağları üzerinde veri iletişimini sağlamak için kullanılan bir yöntemdir. Soketler, iki makine arasında ağ bağlantısı kurarak veri alışverişini sağlar. Bu programlama modeli, istemci-sunucu modeline dayanır ve TCP/IP gibi protokoller üzerinde çalışır.

- **Soket Programlamanın Adımları Nelerdir?**

  Soket programlama genellikle aşağıdaki adımları içerir:

  1. Soket Oluşturma: Sunucu ve istemci tarafında bir soket oluşturulur.
  2. Bağlanma (Bind): Sunucu soketi belirli bir IP adresi ve port numarasına bağlanır.
  3. Dinleme (Listen): Sunucu, istemci bağlantılarını dinlemeye başlar.
  4. Kabul Etme (Accept): Sunucu, istemciden gelen bağlantı isteklerini kabul eder.
  5. Bağlantı Kurma (Connect): İstemci, sunucuya bağlanır.
  6. Veri Gönderme ve Alma: Bağlantı kurulduktan sonra, istemci ve sunucu arasında veri gönderimi ve alımı yapılır.
  7. Bağlantı Kapatma: İşlem tamamlandığında soket kapatılır.

  Örneğin, C++ dilinde soket programlama yaparken `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, `recv()`, ve `close()` gibi fonksiyonlar kullanılır.

  Soket programlama, düşük seviyeli bir ağ programlama tekniği olduğundan, ağ programlarının performansını ve verimliliğini optimize etmek için önemlidir. Özellikle gerçek zamanlı uygulamalar, çevrimiçi oyunlar, sohbet uygulamaları ve web sunucuları gibi projelerde sıkça kullanılır.

- **Soket nedir?**
  Soket (Socket), ağ iletişimi için kullanılan bir arayüzdür ve iletişimde bulunmak isteyen uygulamalar arasında bir bağlantı noktası sağlar. Soket programlama, TCP/IP veya diğer ağ protokollerini kullanarak uygulamalar arasında veri iletişimini sağlar.
  Soket, TCP/IP'de, veri iletişimi için gereken iki bilgi olan IP adresi ve port numarasının yan yana yazılmasıyla oluşan iletişim kanalıdır. Örneğin, 192.168.1.1 makinesine 23 numaralı porttan yapılmış olan bir bağlantı 192.168.1.1:23 şeklinde yazılır.
  Bir soket, \*\*bir ağ üzerindeki iki nokta arasındaki iletişimi temsil eder

- **Soket Türleri**
  Soket programlamada genellikle iki tür soket kullanılır:
  Stream Soket (TCP Soketi): İki uç arasında güvenilir, bağlantı temelli ve sıralı veri iletişimi sağlar. `SOCK_STREAM` türü olarak tanımlanır.
  Datagram Soket (UDP Soketi): Bağlantısız, güvenilir olmayan ve sırasız veri iletişimi sağlar. `SOCK_DGRAM` türü olarak tanımlanır.

 - **Serverda bind() yaptik, Pekii neden client kodunda bind islemi yoktur?**
  Bind İşlemi ve Server Bilgileri
  Bind İşlemi: İstemci tarafında genellikle bind işlemi yapılmasına gerek yoktur. Bind işlemi, sunucu tarafında kullanılır ve sunucunun belirli bir portta dinlemesini sağlar.
  Server Bilgileri: İstemci, sunucuya bağlanmak için sunucunun adres bilgilerini (struct sockaddr_in) belirtir. Bu bilgiler IP adresi ve bağlanılacak portu içerir.
  İstemci kodunda bind işlemi yapmamamızın nedeni, istemcinin dinlemek yerine sunucuya bağlanma amacı taşımasıdır. Sunucu tarafında ise bind işlemi yapılarak belirli bir portta dinlenir ve istemcilerin bağlantı isteklerini kabul eder.
  Bu şekilde istemci, belirli bir sunucuya bağlanarak iletişim kurabilir ve uygulamalar arasında veri transferi yapabilir.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bu proje, temel soket (socket) kavramlarını anlamanıza yardımcı olacak bir örnektir. Tek bir istemcinin bir sunucuya bağlanmasını sağlar ve sunucu ile iletişim kurarak mesajlaşmasını sağlar.

Proje Açıklaması
Bu proje, basit bir TCP/IP soket bağlantısı üzerine kuruludur. İstemci (client) ve sunucu (server) tarafı olmak üzere iki ana bileşeni vardır:

Server (server.c): İstemci bağlantılarını kabul eder ve aldığı mesajları işler.
Client (client.c): Belirli bir sunucuya bağlanır ve sunucuya mesaj gönderir.
Kullanım
Server Başlatma:

./server komutunu kullanarak sunucuyu başlatın.
Sunucu, belirtilen port üzerinde istemci bağlantılarını dinlemeye başlayacaktır.
Client Başlatma:

./client komutunu kullanarak istemciyi başlatın.
İstemci, belirtilen sunucuya bağlanacak ve kullanıcıdan girdi alarak sunucuya mesaj gönderebilecektir.
İletişim:

İstemci bağlandığında ve sunucu mesaj almayı beklediğinde, iletişim başlar.
İstemci herhangi bir mesaj gönderdiğinde, sunucu bu mesajı alacak ve ekrana yazdıracaktır.
Sonlandırma:

İstemci, "exit" komutunu göndererek bağlantıyı sonlandırabilir.
Sunucu, "exit" mesajını aldığında bağlantıyı kapatır ve sonlandırma işlemlerini tamamlar.
Bu proje, başlangıç seviyesinde soket programlama konularını anlamanızı sağlamak için tasarlanmıştır. Tek bir istemcinin sunucuya bağlanması ve iletişim kurması üzerinde odaklanır.


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Tek İstemci ile Sunucu İletişimi Örneği
Bu proje, temel soket (socket) kavramlarını anlamanıza yönelik bir örnektir. Tek bir istemcinin bir sunucuya bağlanmasını ve sunucu ile iletişim kurmasını sağlar.

Çoklu İstemci İletişimi
Birden fazla istemcinin aynı anda sunucu ile iletişim kurabilmesi için çoklu soket programlaması kullanılmalıdır. Çoklu soket programlama, aynı sunucu üzerinde birden fazla bağlantıyı yönetmek için gereklidir. Bu yöntem genellikle şu şekillerde uygulanabilir:

Çoklu İş Parçacığı (Multi-threading): Her istemci bağlantısı için yeni bir iş parçacığı oluşturulur. Her iş parçacığı, bağlantıyı kabul eder, veri alışverişi yapar ve bağlantıyı sonlandırır.

Olay Yönlendirme (Event-Driven): Bir olay döngüsü (event loop) kullanarak tek bir iş parçacığında birden fazla bağlantıyı yönetir. Non-blocking soketler ve olay bildirimleri (event notifications) kullanılarak çoklu bağlantılar eş zamanlı olarak hizmet verir.

Bu örnekte, sadece tek bir istemcinin sunucu ile iletişim kurması gösterilmiştir. Çoklu istemci desteği eklemek için ilgili çoklu soket programlama tekniklerini inceleyebilir ve projenizi bu doğrultuda genişletebilirsiniz.

