# BadUSB: Arduino Pro Micro based BadUSB

### **Nedir?**

BadUSB, yapabildiğim en basit anlatımla, donanımsal imkanlardan faydalanarak
yapılan bir saldırı türü. USB üzerinden bağlanabilen ve belirli özelliklere
sahip bir donanım, içindeki gömülü kod yeniden programlanarak insan arabirim
aygıtı (klavye) gibi çalıştırılabiliyor. Böylece hedef sistemde, USB bağlantı
noktası haricinde bir yere (mesela klavye) dokunmaksızın çok hızlı (saniyede
~300 adet) klavye tuşlaması yapılabiliyor, zararlı yazılım yüklenebiliyor,
sistemde kontrol sağlanabiliyor.

Bu post, yukarıda bahsettiğim saldırı türünü gerçekleştirmek amacıyla yaptığım
BadUSB'nin nasıl yapıldığını anlatacak. Öncesinde ise şunları belirtmem gerek:
BadUSB'yi yaparken YouTube
[Seytonic](https://www.youtube.com/channel/UCW6xlqxSY3gGur4PkGPEUeA) kanalının
yaptığı Arduino devresinden örnek aldım ve kendime göre değiştirdim.

<iframe width="560" height="315" src="https://www.youtube.com/embed/QrwqeI99I8E" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Seytonic projesi switch'le aktifleşen text script'leri çalıştırıyor. Bu tarz
script yazımı ve yazılanları okuması daha kolay. Siz anahtar kelimelerle text
dosyaları oluşturuyorsunuz; Arduino ise bir nevi tercüman gibi satırları
okuyor, tercüme edip uyguluyor. Örneğin:

```txt
DELAY 400

GUI d
DELAY 400

GUI r
DELAY 400
STRING CMD
DELAY 400
ENTER
DELAY 400

STRING CD %TEMP%
DELAY 400
ENTER

STRING NOTEPAD
DELAY 1000
ENTER
```

Ben bu şekilde direktif script'leri yazıp Arduino'nun okuyup işlemesini
beklemek yerine, istediklerimi gerçekleştirecek Arduino C kodunu yazıp
donanıma gömdüm. Belki gelecekte yukarıdaki gibi direktif script'leri ile
çalışan Arduino C kodunu da [projenin GitHub
deposunda](https://github.com/nuriacar/badusb) paylaşırım.

### **Malzemeler ve Bağlantı Diyagramı**

Kendinize bir BadUSB yapabilmeniz için gereken asıl donanım **Atmel MEGA32U4
(ATMega32U4)** mikrodenetleyicisi (aynı özelliklere sahip başka
mikrodenetleyiciler de olabilir). Bu mikrodenetleyici, en basit tabirle,
bilgisayar tarafından insan arabirim aygıtı (klavye) olarak algılanıyor ve
kolay erişilebilir harika bir geliştirme kartı olan **Arduino Pro Micro**
üzerinde yer alıyor. Ayrıca **Atmel MEGA32U4 (ATMega32U4)**
mikrodenetleyicisini taşıyan başka geliştirme kartları da (Arduino Leonardo)
kullanılabilir! **Atmel MEGA32U4 (ATMega32U4)**'ün datasheet'ini okumak
insanın ufkunu açabilir. :)

+ Arduino Pro Micro
+ Micro SD Kart Adaptörü
+ Micro SD Kart
+ 4'lü DIP Switch
+ Breadboard
+ M-M Jumper Kablolar (8 adet)

![Arduino ProMicro BadUSB](/assets/img/arduino-pro-micro-badusb.png)

#### **1. Micro SD Kart Adaptörü → Arduino Pro Micro**

+ GND  → GND (Mavi)
+ VCC  → VCC (Yeşil)
+ MISO → 14  (Sarı)
+ MOSI → 16  (Turuncu)
+ SCK  → 15  (Kırmızı)
+ CS   → 10  (Kahverengi)

#### **2. DIP Switch → Arduino Pro Micro**

+ 1 → 6
+ 2 → 7
+ 3 → 8
+ 4 → 9
+ 1, 2, 3, 4 → GND (Siyah)
+ 1, 2, 3, 4 → RST (Gri)

Gri renkle görsterdiğim 1, 2, 3, 4 → RST (Gri) bağlantısı, reset tuşu gibi
çalışıyor. **DIP switch tarafında** takılı olduğunda Arduino'nun GND ve RST
bağlantı noktaları switch'e ulaşmadan kısa devre olur ve Arduino kapanır,
çıkarıldığında yeni açılmış gibi çalışmaya başlar. Bu şekilde olmazsa her
switch değiştirmede BadUSB'yi USB portundan söküp yeniden takmak gerek. RESET
butonu yapsam daha güzel olacaktı lakin şimdilik bu şekilde M-M jumper kabloyu
söküp takarak resetleme işlemi gerçekleştiriyorum. Bunu şu şekilde
kullanıyorum: RST bağlantısını (Gri Jumper) takıp switch değiştiriyorum,
bağlantıyı çıkarınca Arduino baştan başlıyor ve yeni ayarladığım switch'e
atanmış kodlar çalışıyor. Her switch değiştirmede gri jumper'ı takıp
söküyorum. **Yalnızca DIP switch tarafındaki gri renkle gösterilen RST jumper
ucunu söküp takmak yeterli. Üstteki Arduino RST bağlantısı hep bağlı.**

### **Nasıl Kullanıyorum?**

Arduino Pro Micro'nun hafızası 28KB. Yazdığım firmware bu hafızaya sığıyor
lakin yapmak istediğim extra işlemler için yeterli değil. Micro SD kart bağlı
ama içinden dosya okuma yapabiliyorken içine yazma işlemi yapamıyorum. Ben de
her iki yönde dosya aktarımı ve hedef sisteme program kurulumu yapabilmek için
harici USB/HDD bağlantısı imkanı verecek programlama yaptım.

Şunları yapabiliyor:

+ Harici USB Bellek/HDD içinden dosya okuyup hedef sisteme yazma.
+ Harici USB Bellek/HDD içindeki programı hedef sistemde çalıştırma.
+ Hedef sistemden almak istediğim veriyi harici USB Bellek/HDD içine kopyalama.

Peki nasıl?

+ Harici bir USB/HDD bulun, harfini çok kullanılmayan bir harfle güncelleyin
  (`W:`, `Z:` vb.).
+ İçine `.bat`, `.ps1` dosyaları oluşturup onları BadUSB ile harici USB/HDD
  içinden çalıştırın.

Örnek olarak, '0000' DIP switch durumu için, harici USB/HDD içinden hedef
sisteme netcat.exe kopyalayıp saldırgana reverse shell açan bir payload
dosyası (`netcat-payload.bat`) oluşturup depoya ekledim. Çalışması için harici
USB/HDD içinde `netcat-payload.bat` ile birlikte `netcat.exe` de yer alması
gerekiyor. `netcat.exe` de gene depoda `/assets/exe/` dizini içinde yer alıyor
(overlock makinesi ayağınıza geldi). `netcat-payload.bat` içindeki IP ve port
kısımlarını kendinize göre ayarlamayı ihmal etmeyin.

### **Dikkat!**

Arduino ile `Keyboard.println()` fonksiyonu kullanarak hedef sisteme karakter
dizisi/string göndermek istersek (`Keyboard.println("program_ismi/exe");`)
dikkat etmemiz gereken bir şey var! Arduino, onu yeniden programlarken,
bilgisayar klavyesinde bastığımız tuşları, bizim yazdığımız gibi (Amerikan
klavye dizilimi hariç) görmüyor. Örneğin, sisteme bağlandığında nokta (.)
yazmasını sağlamak için benim sistemimde (TR-Q) noktayı (.) slash (/)
karakteri olarak programlamam gerek. Bunu yaparken de Arduino'nun ASCII
karakter tablosunu baz aldığını düşünmeyin zira almıyor. Teensy, Arduino
Leonardo ve Micro kartları (belki başka kartlar da böyledir ama şimdilik
bildiklerim bunlar) ASCII yerine Amerikan klavye dizilimini (American Keyboard
Layout) baz alıyor. Bkz. [Arduino
Forum](https://forum.arduino.cc/index.php?topic=418813.0)

![Uluslararası Amerikan Klavye Dizilimi](/assets/img/us-international-kb-layout.png)

Daha ayrıntılandıracak olursam şöyle:

Klavye, aslında üzerinde yazan karakteri/harfi ('a', 'z', '5' vb.) işletim
sistemine iletmez: Tuş basmasını iletir ama o tuşun nasıl yorumlanacağı
işletim sisteminin dil ayarlarına bağlıdır. Örneğin, klavye der ki: Aşağıdan
yukarı 3. sıra, soldan 2. tuş basıldı. Pek çok klavyede bu dizilimdeki tuş 'a'
karakteridir ve işletim sistemi dil ayarlarına bakarak bunu 'a' olarak
algılar. Peki Arduino kartını sisteme bağladığımda hedefte 'ö' veya 'ç'
karakterlerini yazdırmasını istersem? Bunun için benim sistemimde (TR-Q),
alttan 2. sırada yer alan, M karakterinin sağındaki 'ö' ve 'ç' tuşlarını
değil, 'ö' için '<', ç için '>' şeklinde kaynak kod içi karakter dizisi/string
yazımı yapmam gerek. Özetle şunu yapın:

+ Klavyenize bakın ve hedef sistemde yazdırmak istediğiniz karakterin
  klavyenizdeki fiziksel yerini bulun.
+ Aynı tuş fiziksel yer olarak uluslararası Amerikan klavye düzeninde
  (yukarıdaki görsel) hangi karaktere denk geliyorsa kendi klavyenizde o
  karakterin tuşuna basın.

Benim sistemimde (TR-Q), BadUSB ile `Keyboard.println()` fonksiyonu kullanarak
'.' yazdırmak için '/', 'ö' yazdırmak için '<', 'ç' yazdırmak için '>' vb.
şeklinde kaynak kod içi karakter dizisi/string programlamam gerek.

Belki gelecekte `Keyboard.println()` fonksiyonu içindeki karakter
dizilerini/stringleri TR-Q'dan US-International klavye dizilimine tercüme eden
bir programı da GitHub hesabımda paylaşırım. Siz yazarsanız lütfen gönderin,
depoya ekleyeyim.

### **Başka?**

Yukarıda donanım planını paylaştığım BadUSB ile yapacağınız işlemler için
gereken standart program kalıbını GitHub hesabıma ekledim. `switch` içindeki
`case`leri keyfinizce modifiye ederek 16 farklı script çalıştırabilirsiniz
(4'lü DIP switch, ikilik tabanda (0 - 1) 2 üzeri 4'ten 16 farklı script
çalıştırılabilmesine imkan tanıyor). Arduino IDE ile kaynak kodu düzenleyip
Arduino Pro Micro'yu güncelleyin. Hepsi bu.

