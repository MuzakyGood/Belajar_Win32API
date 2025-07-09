#include <windows.h>

#define CHANGE_TEXT_FEATURE_MENU 1
#define EXIT_FEATURE_MENU 2
#define ABOUT_MENU 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HWND hEditOutput;

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

                case CHANGE_TEXT_FEATURE_MENU:
                    wchar_t text[100];

                    GetWindowTextW(hEditOutput, text, 100);
                    SetWindowTextW(hWnd, text);
                break;

                case EXIT_FEATURE_MENU:
                    DestroyWindow(hWnd);
                break;

                case ABOUT_MENU:
                    MessageBoxA(NULL, "This app draw text and input text GUI Win32 API.\nWrite in C++23.\nCreated by Zach Noland in 2025.", "About Tutorial", MB_ICONINFORMATION);
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
    HMENU hFile;

    hMenu = CreateMenu();
    hFile = CreateMenu();

    AppendMenuW(hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hFile), L"Feature");
    AppendMenuW(hFile, MF_STRING, CHANGE_TEXT_FEATURE_MENU, L"Change Text");

    AppendMenuW(hFile, MF_SEPARATOR, static_cast<UINT_PTR>(NULL), NULL);
    AppendMenuW(hFile, MF_STRING, EXIT_FEATURE_MENU, L"Exit");

    AppendMenuW(hMenu, MF_STRING, ABOUT_MENU, L"About");

    SetMenu(hWnd, hMenu);
}

void addControls(HWND hWnd) {
    CreateWindowW(L"STATIC", L"Renamed Name APP", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 5, 100, 50, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"Enter Text :", WS_VISIBLE | WS_CHILD | SS_LEFT, 25, 65, 100, 50, hWnd, NULL, NULL, NULL);
    hEditOutput = CreateWindowW(L"EDIT", L".....", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 108, 65, 200, 50, hWnd, NULL, NULL, NULL);
}