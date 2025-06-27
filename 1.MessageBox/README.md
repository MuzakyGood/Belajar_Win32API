# Membuat Message Box Sederhana

## A.Deskripsi
Pada kesempatan kali ini saya akan membuat message box sederhana dengan Win32 API.<br>
Kodenya cukup simple dan mudah di pahami. Message box berisi title/judul ``"First GUI"`` text/pesan ``"Hello, World!"``.

## B.Penjelasan Kode

1. Include header dari Win32 API yaitu ``<windows.h>``.

```cpp
#include <windows.h>
```

Header ini hanya tersedia _kemungkinan_, jika sudah mengunduh di website resmi **Microsoft**, jika sudah install extensi C++ di vscode, sudah install **W64DevKit**, atau mungkin bawaan windows.

2. Struktur kode tidak menggunakan ``int main() { return 0;}``, Tetapi menggunakan struktur ``WINAPI``,

```cpp
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    // Isi kode
    return 0;
}
```

- **WINAPI** atau bisa di sebut juga ``__stdcall`` biasa di sebut call conversion di windows.<br>
Berfungsi sebagai tempat argumen di lewatkan ke dalam fungsi, dan bagaimana nilai di kembalikan.<br>
``WINAPI`` wajib ada.
- **WinMain** sebagai fungsi utama pengganti ``main``.<br>
``WinMain`` memiliki beberapa argument seperti ``HINSTANCE hInst``