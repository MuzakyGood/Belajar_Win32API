#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_OPEN_SUBMENU_ITEM 2
#define FILE_MENU_EXIT 3
#define ABOUT_MENU 4
#define HELP_MENU 5

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND);

HMENU hMenu;

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

                case FILE_MENU_NEW:
                    MessageBeep(MB_OK);
                break;

                case FILE_MENU_EXIT:
                    DestroyWindow(hWnd);
                break;

                case ABOUT_MENU:
                    MessageBoxA(NULL, "This concept GUI Win32 API.\nWrite in C++23.\nCreated by Zach Noland in 2025.", "Information", MB_ICONINFORMATION);
                break;

                case HELP_MENU:
                    MessageBoxA(NULL, "Notes: No help or Tutorial.\nJust Empty Window with Menus.", "Help", MB_HELP);
                break;

            }
        break;

        case WM_CREATE:
            addMenus(hWnd);
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
    HMENU hFileMenu = CreateMenu();
    HMENU hSubFileMenu = CreateMenu();

    AppendMenuW(hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hFileMenu), L"File");

    AppendMenuW(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
    
    AppendMenuW(hFileMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hSubFileMenu), L"Open");
    AppendMenuW(hSubFileMenu, MF_STRING, FILE_OPEN_SUBMENU_ITEM, L"Item");
    
    AppendMenuW(hFileMenu, MF_SEPARATOR, static_cast<UINT_PTR>(NULL), NULL);
    AppendMenuW(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

    AppendMenuW(hMenu, MF_STRING, ABOUT_MENU, L"About");
    AppendMenuW(hMenu, MF_STRING, HELP_MENU, L"Help");

    SetMenu(hWnd, hMenu);
}