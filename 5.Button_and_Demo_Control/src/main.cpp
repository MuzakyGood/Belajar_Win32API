#include <iostream>
#include <vector>
#include <windows.h>

#define ABOUT_MENU 1
#define EXIT_MENU 2
#define GENERATE_BUTTON 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hName, hAge, hOutput;
HMENU hMenu;

void addMenus(HWND);

void addControls(HWND);

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

                case ABOUT_MENU:
                    MessageBoxA(NULL, "This Demo Aplication GUI Win32 API.\nWrite in C++23.\nCreated by Zach Noland in 2025.", "About Tutorial", MB_ICONINFORMATION);
                break;

                case EXIT_MENU:
                    DestroyWindow(hWnd);
                break;

                case GENERATE_BUTTON:
                    std::vector<char> NameBuffer(30), AgeBuffer(10);

                    GetWindowTextA(hName, NameBuffer.data(), NameBuffer.size());
                    GetWindowTextA(hAge, AgeBuffer.data(), AgeBuffer.size());

                    std::string Name(NameBuffer.data());
                    std::string Age(AgeBuffer.data());
                    std::string Output = Name + " is " + Age + " years old.";

                    SetWindowTextA(hOutput, Output.c_str());

                break;

            }
        break;

        case WM_CREATE:
            addMenus(hWnd);
            addControls(hWnd);
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

void addMenus(HWND hWnd) {
    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, ABOUT_MENU, L"About");
    AppendMenuW(hMenu, MF_STRING, EXIT_MENU, L"Exit");

    SetMenu(hWnd, hMenu);
}

void addControls(HWND hWnd) {
    CreateWindowW(L"STATIC", L"Text Generator", WS_VISIBLE | WS_CHILD, 200, 25, 100, 50, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"Name :", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"EDIT", L".....", WS_VISIBLE | WS_CHILD | WS_BORDER, 158, 50, 98, 20, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"Age :", WS_VISIBLE | WS_CHILD, 100, 80, 98, 38, hWnd, NULL, NULL, NULL);
    hAge = CreateWindowW(L"EDIT", L".....", WS_VISIBLE | WS_CHILD | WS_BORDER, 158, 80, 98, 20, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"BUTTON", L"Generate", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 130, 100, 25, hWnd, reinterpret_cast<HMENU>(GENERATE_BUTTON), NULL, NULL);

    hOutput = CreateWindowW(L"EDIT", L"No Output", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 180, 300, 200, hWnd, NULL, NULL, NULL);
}