#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <windows.h>

// Preprocessor define

#define OPEN_FILE_MENU 1
#define SAVE_FILE_MENU 2
#define SAVE_AS_FILE_MENU 3
#define EXIT_FILE_MENU 4
#define FEATURE_MENU 5
#define ABOUT_MENU 6

// Global Deklarasi

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HWND hInFile, hPathFile;

std::string pathFileHandle;

void addMenus(HWND);
void addControl(HWND);

void openFileMenu(HWND);
void saveFileMenu(HWND);
void saveAsFileMenu(HWND);

void fileOpenAndRead(std::string);
void fileOpenAndWrite(std::string);

// =====Win32 API user interface=====

// utama dari aplikasi menggunakan WinMain()
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    
    WNDCLASSW wc = {0};
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"firstWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) {
        return -1;
    }

    CreateWindowW(L"firstWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessageW(&msg, NULL, static_cast<UINT>(NULL), static_cast<UINT>(NULL))) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// Window Procedure
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

    switch (msg) {

        case WM_COMMAND:
            switch (wp) {

                case OPEN_FILE_MENU:
                    openFileMenu(hWnd);
                break;

                case SAVE_FILE_MENU:
                    saveFileMenu(hWnd);
                break;

                case SAVE_AS_FILE_MENU:
                    saveAsFileMenu(hWnd);
                break;

                case EXIT_FILE_MENU:
                    DestroyWindow(hWnd);
                break;

                case FEATURE_MENU:
                    MessageBoxW(NULL, L"1.Add Input text feature.\n2.Save and Save as.\n3.Add scroll bar input text.", L"App Feature", MB_OK | MB_ICONINFORMATION);
                break;

                case ABOUT_MENU:
                    MessageBoxW(NULL, L"Write in C++ with Win32 API.\nCreated by Zach Noland in 2025.", L"About App", MB_OK | MB_ICONQUESTION);
                break;
            }
        break;

        case WM_CREATE:
            addMenus(hWnd);
            addControl(hWnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return DefWindowProcW(hWnd, msg, wp, lp);
}

// Inisilisasi Procedure

// Procedure membuat tampilan menu.
void addMenus(HWND hWnd) {
    hMenu = CreateMenu();
    HMENU hOpenFiles = CreateMenu();

    AppendMenuW(hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hOpenFiles), L"Files");
    AppendMenuW(hOpenFiles, MF_STRING, OPEN_FILE_MENU, L"Open");
    AppendMenuW(hOpenFiles, MF_STRING, SAVE_FILE_MENU, L"Save");
    AppendMenuW(hOpenFiles, MF_STRING, SAVE_AS_FILE_MENU, L"Save As...");
    AppendMenuW(hOpenFiles, MF_SEPARATOR, static_cast<UINT_PTR>(NULL), NULL);
    AppendMenuW(hOpenFiles, MF_STRING, EXIT_FILE_MENU, L"Exit");

    AppendMenuW(hMenu, MF_STRING, FEATURE_MENU, L"Feature");
    AppendMenuW(hMenu, MF_STRING, ABOUT_MENU, L"About");

    SetMenu(hWnd, hMenu);
}

// Procedure membuat tampilan window.
void addControl(HWND hWnd) {
    CreateWindowW(L"STATIC", L"Text Editor", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 20, 100, 50, hWnd, NULL, NULL, NULL);

    hInFile = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE, 50, 50, 380, 300, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"File Path:", WS_VISIBLE | WS_CHILD, 50, 360, 100, 24, hWnd, NULL, NULL, NULL);
    hPathFile = CreateWindowW(L"EDIT", L"C:\\", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 50, 380, 380, 24, hWnd, NULL, NULL, NULL);
}

// ==============================

// =====Text Editor App code=====

// Kode membaca file.
void fileOpenAndRead(std::string pathFile) {
    std::fstream userfile(pathFile, std::ios::in | std::ios::binary);

    if (userfile.is_open()) {
        std::string Text((std::istreambuf_iterator<char>(userfile)), std::istreambuf_iterator<char>());

        SetWindowTextA(hInFile, Text.c_str());

        userfile.close();
    } else {
        userfile.close();
    }
}


// Kode menulis file.
void fileOpenAndWrite(std::string pathFile) {
    int sizeWindowText;
    sizeWindowText = GetWindowTextLengthA(hInFile);
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

// Menu membuka file.
void openFileMenu(HWND hWnd) {
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

    GetOpenFileNameA(&openfn);

    pathFileHandle = openfn.lpstrFile;

    fileOpenAndRead(pathFileHandle);

    SetWindowTextA(hPathFile, openfn.lpstrFile);
}

// Menu menyimpan(save) file.
void saveFileMenu(HWND hWnd) {
    if ((pathFileHandle == "")) {
        saveAsFileMenu(hWnd);
    } else {
        fileOpenAndWrite(pathFileHandle);
    }
}

// Menu menyimpan file baru(save as).
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
// ==============================