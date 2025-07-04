# Mengenal Win32 API di C/C++

## 📌Deskripsi📌

**Win32 API** adalah pemrograman UI(user interface) aplikasi (API) utama yang disediakan oleh Microsoft Windows untuk mengakses fitur-fitur sistem operasi, seperti pembuatan jendela (window), pengolahan pesan (message handling), pengelolaan file, input perangkat keras, dan banyak lagi.

API ini ditulis dalam bahasa C, namun dapat digunakan dalam C++. Win32 API memungkinkan pengembang membuat aplikasi native Windows tanpa menggunakan framework tambahan.

## Sejarah Singkat Win32 API

Win32 API dikembangkan oleh Microsoft sebagai bagian dari keluarga Windows API (WinAPI), yang dimulai sejak era **Windows 1.0** pada tahun 1985. Seiring perkembangan Windows, API ini terus disempurnakan dan menjadi tulang punggung pengembangan aplikasi desktop di sistem operasi Windows.

Nama "Win32" merujuk pada versi Windows yang mendukung arsitektur 32-bit, dimulai sejak **Windows NT** dan **Windows 95**. Meskipun Windows modern kini sudah 64-bit, Win32 API tetap digunakan dan kompatibel, serta menjadi dasar dari banyak framework seperti **MFC**, **.NET**, dan **WinForms**.

---

## Alasan menggunakan Win32 API?

- Ringan dan cepat.
- Akses langsung ke fitur-fitur Windows tanpa layer tambahan.
- Cocok untuk aplikasi sistem dan utilitas low level programming.

---

## Perlu diperhatikan

- Win32 API hanya bekerja pada OS Windows.
- Win32 API harus di install terlabih dahulu jika belum tersedia.
- Jika Window tidak muncul, kemungkinan ada kode yang salah.
- Di tutorial ini saya akan menggunakan C++ dan fitur bawaan-nya, Jadi pastikan run code ini di C++.

---

## 📜Syarat memahami Win32 API📜
Di sini saya bagikan tips cepat paham jika tidak, bisa belajar fundamental lagi. Di Win32 API banyak menggunakan preprocessor seperti ``#define``, pointer, struct, procedure dan function, penggunaan variable pointer. Jadi sebelum mencoba atau memulai dengan Win32 API, Pembaca harus;

Utama:
- Expert di bahasa pemrograman **C**.
- Memahami fundamental bahasa pemrograman **C++**.
- Memahami struktur membuat aplikasi dari kode.

<details>
  <summary>Di jabarkan satu-persatu 🔽</summary>
  <br>
  <ul>
    <li>Memahami mekanisme Preprocessor seperti <code>#define</code> di <b>C</b> atau <b>C++</b>.</li>
    <li>Memahami call conversion pointer di <b>C</b>.</li>
    <li>Memahami mekanisme <b>pointer</b>.</li>
    <li>Memahami casting tipe data di <b>C</b> atau <b>C++</b>.</li>
    <li>Memahami procedure atau function di <b>C</b> atau <b>C++</b>.</li>
    <li>Memahami tipe data struct di <b>C</b> atau <b>C++</b>.</li>
    <li>Memahami percabangan di <b>C</b> atau <b>C++</b>.</li>
    <li>Memahami string di <b>C++</b>.</li>
  </ul>
</details>
<br>

> Catatan: Bagian **Utama** sudah mencakup semua, Bagian **Di jabarkan satu-persatu** jika mau tau lebih detail.

---

## 🛠️Tools yang Dibutuhkan🛠️

- Compiler seperti `cl.exe` (Visual Studio) atau `g++` (Mingw/W64DevKit).
- Teks editor seperti VS Code.
- SDK Windows (biasanya sudah termasuk di Visual Studio).

> **Catatan:** Untuk compile Win32 API tidak memerlukan flag khusus, hanya command biasa. Contoh: ``g++ main.cpp -o main``.

---

## 💾Struktur Belajar💾

1. [Membuat Message Box Sederhana](https://github.com/MuzakyGood/Belajar_Win32API/tree/main/1.MessageBox)
2. [Membuat Window Sederhana](https://github.com/MuzakyGood/Belajar_Win32API/tree/main/2.CreateWindow)
3. [Membuat Menu Window Sederhana](https://github.com/MuzakyGood/Belajar_Win32API/tree/main/3.CreateMenu)
4. [Membuat Text Input dan Output di Window](https://github.com/MuzakyGood/Belajar_Win32API/tree/main/4.Static_Edit_Control)
5. [Membuat Button dan Demo App](https://github.com/MuzakyGood/Belajar_Win32API/tree/main/5.Button_and_Demo_Control)
6. [Memuat gambar BMP sederhana](https://github.com/MuzakyGood/Belajar_Win32API/tree/main/6.CreateBmpImage)
7. [Membuat dialog di Message Box](https://github.com/MuzakyGood/Belajar_Win32API/tree/main/7.CreateMessageBox_Dialog)
> Next Coming Soon. Selamat Belajar 😉

---

## 📘Referensi📘

- [Dokumentasi Resmi Microsoft - Win32 API](https://learn.microsoft.com/en-us/windows/win32/api/)
- Buku: *Programming Windows* oleh Charles Petzold

---

## 📎License📎

```txt
MIT License

Copyright (c) 2025 Zach Noland

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

# 😉Terima Kasih😉