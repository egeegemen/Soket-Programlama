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

