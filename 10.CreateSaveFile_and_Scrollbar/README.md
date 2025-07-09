# Membuat Fitur Save, Save As, dan Scroll Bar

## A. Deskripsi

Program ini merupakan aplikasi GUI berbasis **Win32 API** yang bertindak sebagai text editor sederhana. Aplikasi memungkinkan pengguna untuk:

* Membuka file teks atau file kode `.txt`, `.c`, atau `.cpp`.
* Menyimpan perubahan ke file yang sama menggunakan **Save**.
* Menyimpan ke file baru dengan **Save As...**.
* Menampilkan isi file dan path yang sedang aktif.

Fitur tambahan yang tersedia:

* Scroll bar **horizontal dan vertikal** untuk area teks.
* Menu bar dengan kategori "Files" berisi submenu:

  * `Open`
  * `Save`
  * `Save As...`
  * `Exit`

---

## B. Penjelasan Kode

### 1. Preprocessor define

```cpp
#define SAVE_FILE_MENU 2
#define SAVE_AS_FILE_MENU 3
```

`#define SAVE_FILE_MENU 2` Digunakan untuk fitur save. Preprocessornya mengembalikan interger 2 agar dapat di handle Window Procedure.

`#define SAVE_AS_FILE_MENU 3` Digunakan untuk fitur save as. Preprocessornya mengembalikan interger 3 agar dapat di handle Window Procedure.

### 2. Menu Save (SAVE\_FILE\_MENU)

```cpp
void saveFileMenu(HWND hWnd) {
    if ((pathFileHandle == "")) {
        saveAsFileMenu(hWnd);
    } else {
        fileOpenAndWrite(pathFileHandle);
    }
}
```

* Jika `pathFileHandle` kosong (belum ada file dibuka), maka fungsi **Save** akan bertindak seperti **Save As**.
* Jika sudah ada file, maka akan langsung menulis ulang isinya.
* Proses penulisan menggunakan fungsi `fileOpenAndWrite()`.

### 3. Menu Save As (SAVE\_AS\_FILE\_MENU)

```cpp
void saveAsFileMenu(HWND hWnd) {
    std::vector<char> fileName(100);
    OPENFILENAMEA openfn;
    ZeroMemory(&openfn, sizeof(openfn));
    openfn.lStructSize = sizeof(openfn);
    openfn.hwndOwner = hWnd;
    openfn.lpstrFile = fileName.data();
    openfn.lpstrFile[0] = '\0';
    openfn.nMaxFile = fileName.size();
    openfn.lpstrFilter = "All file\0*.TXT;*.C;*.CPP\0Text file\0*.TXT\0C/C++ code file\0*.C;*.CPP\0";
    openfn.nFilterIndex = 1;
    GetSaveFileNameA(&openfn);
    pathFileHandle = openfn.lpstrFile;
    fileOpenAndWrite(pathFileHandle);
}
```

* Menampilkan dialog simpan file baru.
* Menyimpan path file ke `pathFileHandle` agar bisa digunakan untuk proses save berikutnya.
* Memanggil fungsi `fileOpenAndWrite()` untuk menyimpan isi teks ke file yang dipilih.

> Catatan: Pastikan untuk menyertakan flag `-lcomdlg32` ketika ingin compile kode main.cpp, karena agar compiler dapat menyertakan menyertakan library `comdlg32.lib` dan tersedia procedure `GetOpenFileName();`, `GetSaveFileName();`.

### 4. Fungsi Menulis File

```cpp
void fileOpenAndWrite(std::string pathFile) {
    int sizeWindowText = GetWindowTextLengthA(hInFile);
    std::vector<char> TextBuffer(sizeWindowText + 1);
    std::fstream userfile(pathFile, std::ios::out | std::ios::binary);
    if (userfile.is_open()) {
        GetWindowTextA(hInFile, TextBuffer.data(), sizeWindowText + 1);
        userfile << TextBuffer.data();
        userfile.close();
    } else {
        userfile.close();
    }
}
```

* Mengambil seluruh isi dari `EDIT control` menggunakan `GetWindowTextA`.
* Menulis isi tersebut ke dalam file menggunakan `fstream`.
* Mode penulisan `std::ios::binary` digunakan untuk memastikan byte ditulis sesuai aslinya.

### 5. Scroll Bar pada Area Text (hInFile)

```cpp
hInFile = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE, ...);
```

* `WS_VSCROLL`: Menambahkan scroll bar vertikal.
* `WS_HSCROLL`: Menambahkan scroll bar horizontal.
* `ES_MULTILINE`: Mengizinkan teks tampil dalam banyak baris.

Scroll bar sangat penting untuk membaca atau mengedit file berukuran panjang.

---

## C. Hasil

Ketika program dijalankan:

* Area teks dapat diedit dengan bebas.
* Scroll bar aktif saat isi file melebihi ukuran area teks.

![Results File Viewer (Write)](../image/ResultsFileViewer(Write).png)

* Menu `Files > Open` dapat digunakan untuk membuka file.
* Menu `Files > Save` akan menyimpan ke file terakhir yang dibuka atau disimpan.
* Menu `Files > Save As...` memungkinkan menyimpan ke file baru.
* Menu `Files > Exit` dapat di gunakan untuk menutup aplikasi.

![Menu Save and Save as](../image/MenuSaveAndSaveAs(Write).png)

* Tampilan `Save As...` file menu.
* Anda dapat memasukan nama file beserta formatnnya atau me-replace dari file sebelumnya.

![Save as File Menu](../image/SaveasFileMenu(Write).png)

---

## 😉 Terima Kasih 😉