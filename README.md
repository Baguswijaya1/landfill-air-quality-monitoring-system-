# AQUOS - Air Quality Monitoring System

Repository ini adalah dokumentasi dan panduan penggunaan AQUOS (Air Quality Monitoring System), alat pemantau kualitas udara untuk area di sekitar tempat pembuangan sampah. Projek ini adalah Program Kerja KKN-PPM UGM di Desa Sumberrejo, Kecamatan Batur, Kabupaten Banjarnegara.

## ✨ Fitur Utama
- **Mendeteksi tiga jenis gas berbahaya** yang umum ditemui di tempat pembuangan sampah, seperti gas Metana (CH<sub>4</sub>), Amonia (NH<sub>3</sub>), dan Asam Sulfida (H<sub>2</sub>S).
- Pemantauan secara langsung lewat **LCD display** maupun melalui *smartphone* menggunakan **local dashboard**, sehingga bisa diakses di area sekitar alat.
- **Menggunakan sensor dan komponen biaya murah** (MQ2, MQ135, MQ135, ESP32).
- **Sistem yang dirancang modular**, memudahkan  penggantian sensor dan komponen apabila terjadi kerusakan.

# :orange_book:Panduan Penggunaan Alat
### :battery: Menyalakan AQUOS
1. Hubungkan port USB type-C pada alat dengan sumber tenaga dengan tegangan 5V dan daya 25W. 
2. Anda bisa mentenagai alat menggunaakan adaptor charger smartphone 25W ke stop kontak rumah/gedung.
3. Nyalakan Saklar.
4. Alat akan aktif dan mulai mengambil data gas di lingkungan sekitar. Tunggu 10 menit untuk mendapat data sensor yang lebih akurat, karena sensor membutuhkan penyesuaian terlebih dahulu setelah dinyalakan

### :desktop_computer: Memantau kualitas udara lewat LCD
1. Hasil pengukuran tingkat kepekatan gas dapat dilihat langsung pada layar LCD.

### :signal_strength: Memantau Kualitas Udara Melalui *Smartphone*/Komputer dengan *Local Dashboard*
AQUOS tidak memerlukan akses internet untuk bisa dipantau lewat perangkat pribadi. Sebaliknya, alat ini berperan sebagai *access point*, dan data sensor dapat diakses dengan menghubungkan perangkat pribadi dengan koneksi alat dan masuk ke alamat IP alat lewat aplikasi *browser*. Berikut ini adalah langkah-langkahnya.
1. **Nyalakan alat**
2. **Siapkan perangkat pribadi** (smartphone/komputer) dan **hubungkan dengan jaringan yang disediakan oleh AQUOS**.
```
SSID = AQUOS-Batur
Password = Batur123
```
SSID dan password dapat dikustomisasi dengan mengubah kode program di *aquos_code/include/access_point.h* 

4. **Buka aplikasi browser** lalu pergi ke alamat IP dari AQUOS dengan mengetik **192.168.4.1** pada panel penelusuran
5. Sekarang kamu bisa melihat kualitas udara saat ini. **Refresh halaman browser** untuk mendapatkan pembaruan data.

# Perawatan dan Pengembangan
## :hammer_and_wrench: Komponen Utama
| Nama Komponen | Fungsi | 
|:-------------------------|:----------------------:|
| ESP32 DevKit V1                    | Microcontroller sebagai Unit Pemroses Utama      |
| MQ2                      | Sensor Gas Metana (CH<sub>4</sub>)                          |
| MQ135                    | Sensor Gas Amonia (NH<sub>3</sub>)                          |
| MQ136                    | Sensor Gas Asam Sulfida (H<sub>2</sub>S)                    |
| LCD 16x2                 | Komponen untuk menampilkan bacaan sensor         |
| Modul TXS0108E           | Logic Level Shifter untuk konversi tegangan data keluar dan masuk ESP32|
</div>

## :construction: Struktur Projek


Projek ini terdiri dari tiga bagian utama:
* **aquos_code**: berisi kode program dari projek ini. Dibuat menggunakaan Arduino Framework dan PlatformIO.
* **aquos_pcb**: berisi desain PCB dari projek ini. Dapat dibuka menggunakan software KiCad 12.0.
* **aquos_chasing**: berisi desain chasing dari projek ini. Dibuat menggunakan Autodesk Inventor.

## :computer: Pengembangan
Projek ini adalah projek open-source. Anda bebas untuk menggunakan repository ini untuk projek Anda ataupun untuk pengembangan lebih lanjut.

```
git clone https://github.com/Baguswijaya1/landfill-air-quality-monitoring-system-.git
```
Untuk diskusi lebih lanjut, Anda dapat melakukan kontak dengan saya melalui email bagusanw@gmail.com
