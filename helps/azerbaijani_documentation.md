# Havoc Demon - Genişləndirilmiş Komanda Sənədləri (Azərbaycanca)

Orijinal Layihə Linki: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)

---

### help
Göstərilən komandanın kömək mesajını göstərir.
**İstifadə:** `help [komanda]`
Demon agentində mövcud olan hər hansı bir komanda və ya modul üçün sistem daxili kömək və istifadə detallarını siyahıya alır. Parametr daxil edilməzsə, bütün komandaların siyahısını qaytarır.
**Nümunələr:**
- `help`
- `help inline-execute`

### sleep
Yuxu gecikməsini və kənarlaşma faizini (jitter) təyin edir.
**İstifadə:** `sleep [gecikmə] (kənarlaşma)`
Demon-un Teamserver (komanda serveri) ilə əlaqə qurma (check-in) intervalını təyin edir. "Jitter" parametri faizlə göstərilir və şəbəkədəki müntəzəm trafik nümunəsini pozaraq təhlükəsizlik sistemlərindən gizlənməyə kömək edir.
**Nümunələr:**
- `sleep 10`
- `sleep 60 15`

### proc list
Hədəf üzərində işləyən proseslərin siyahısını göstərir.
**İstifadə:** `proc list`
Hədəf maşında o an aktiv olan prosesləri (Proses ID, ad, arxitektura və s.) ətraflı şəkildə sadalayır.
**Nümunələr:**
- `proc list`

### shell
cmd.exe üzərindən komanda icra edib nəticəni alır.
**İstifadə:** `shell [komandalar]`
Windows əmr sətri (cmd.exe) vasitəsilə komanda icra edir. Nəticə birbaşa operatora göndərilir.
**Nümunələr:**
- `shell dir c:\windows\system32`

### token steal
Göstərilən prosesdən token oğurlayır.
**İstifadə:** `token steal [pid] (handle)`
Yüksək imtiyazlı bir prosesin token-ini oğurlayır və daha sonra istifadə etmək üçün kimlik kassasına (Vault) qeyd edir.
**Nümunələr:**
- `token steal 1337`

---
Orijinal Layihə Linki: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)