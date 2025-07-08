#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <windows.h>

#define OPEN_FILE_MENU 1
#define SAVE_AS_FILE_MENU 2
#define EXIT_FILE_MENU 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HWND hInFile, hPathFile;

void addMenus(HWND);

void addControl(HWND);

void openFileMenu(HWND);
void saveFile(HWND);

void fileOpenAndRead(std::string);
void fileOpenAndWrite(std::string);

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

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

    switch (msg) {

        case WM_COMMAND:
            switch (wp) {

                case OPEN_FILE_MENU:
                    openFileMenu(hWnd);
                break;

                case SAVE_AS_FILE_MENU:
                    saveFile(hWnd);
                break;

                case EXIT_FILE_MENU:
                    DestroyWindow(hWnd);
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

void fileOpenAndWrite(std::string pathFile) {
    int sizeWindowText;
    sizeWindowText = GetWindowTextLengthA(hInFile);
    std::vector<char> TextBuffer(sizeWindowText + 1);
    std::fstream userfile(pathFile, std::ios::out);

    if (userfile.is_open()) {

        GetWindowTextA(hInFile, TextBuffer.data(), sizeWindowText + 1);

        userfile << TextBuffer.data();

        userfile.close();
    } else {
        userfile.close();
    }
}

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

    fileOpenAndRead(openfn.lpstrFile);

    SetWindowTextA(hPathFile, openfn.lpstrFile);
}

void saveFile(HWND hWnd) {
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

    fileOpenAndWrite(openfn.lpstrFile);
}

void addMenus(HWND hWnd) {
    hMenu = CreateMenu();
    HMENU hOpenFiles = CreateMenu();

    AppendMenuW(hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hOpenFiles), L"Files");
    AppendMenuW(hOpenFiles, MF_STRING, OPEN_FILE_MENU, L"Open");
    AppendMenuW(hOpenFiles, MF_STRING, SAVE_AS_FILE_MENU, L"Save As...");
    AppendMenuW(hOpenFiles, MF_SEPARATOR, static_cast<UINT_PTR>(NULL), NULL);
    AppendMenuW(hOpenFiles, MF_STRING, EXIT_FILE_MENU, L"Exit");


    SetMenu(hWnd, hMenu);
}

void addControl(HWND hWnd) {
    CreateWindowW(L"STATIC", L"File Viewer", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 20, 100, 50, hWnd, NULL, NULL, NULL);

    hInFile = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 50, 50, 380, 300, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"File Path:", WS_VISIBLE | WS_CHILD, 50, 360, 100, 24, hWnd, NULL, NULL, NULL);
    hPathFile = CreateWindowW(L"EDIT", L"C:\\", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 50, 380, 380, 24, hWnd, NULL, NULL, NULL);
}