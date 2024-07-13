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

# Basit Soket Programlama Örneği

Bu proje, **soket programlama** kavramlarını anlamanıza yardımcı olacak temel bir örnektir. Odak noktası, **tek bir istemci** ile **sunucu** arasındaki iletişimi sağlamaktadır.

## Proje Açıklaması

Bu proje, basit bir **TCP/IP soket bağlantısı** üzerine kuruludur ve iki temel bileşeni içermektedir:

**Sunucu (`server.c`)**

Sunucu, istemci bağlantılarını kabul eder ve alınan mesajları işler.

**İstemci (`client.c`)**

İstemci, belirtilen sunucuya bağlanır ve ona mesaj gönderebilir.

## Kullanım

### Sunucuyu Başlatma:

Sunucuyu başlatmak için aşağıdaki komutu kullanın:

```bash

./server
```

Sunucu, belirtilen bağlantı noktasında istemci bağlantılarını dinlemeye başlar.

### İstemciyi Başlatma:

İstemciyi başlatmak için aşağıdaki komutu kullanın:

```bash

./client
```

İstemci, sunucuya bağlanacak ve ona mesaj göndermenize olanak tanıyacaktır.

## İletişim

İstemci bağlandığında ve sunucu mesaj almayı beklediğinde, iletişim başlar. İstemci bir mesaj gönderdiğinde, sunucu bu mesajı alır ve konsolda görüntüler.

## Bağlantıyı Sonlandırma

Bağlantıyı sonlandırmak için istemci "**exit**" komutunu gönderebilir. Bu komutu aldığında, sunucu bağlantıyı kapatır ve sonlandırma işlemlerini tamamlar.

## Proje Genişletme

Bu proje, temel **soket programlama** örnekleri sunar. **Birden fazla istemci** ile iletişim için **çoklu soket programlama** tekniklerini (örneğin **çoklu iş parçacığı** , **olay yönlendirme yaklaşımları ya da select() ** ) keşfetmeyi ve uygulamayı düşünebilirsiniz.
