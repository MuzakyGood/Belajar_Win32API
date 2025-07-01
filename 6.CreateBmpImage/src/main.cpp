#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hLandscape1;
HBITMAP hGenerateImage, hLandscape1Image;

void loadImage();
void addControl(HWND);

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

        case WM_CREATE:
            loadImage();
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

void addControl(HWND hWnd) {
    CreateWindowW(L"STATIC", L"Tutorial BMP Load", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 25, 100, 50, hWnd, NULL, NULL, NULL);

    hLandscape1 = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_BITMAP, 130, 100, 100, 50, hWnd, NULL, NULL, NULL);
    SendMessageW(hLandscape1, STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(hLandscape1Image));

    HWND hBut = CreateWindowW(L"Button", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | BS_BITMAP, 200, 280, 100, 30, hWnd, NULL, NULL, NULL);
    SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(hGenerateImage));
}

void loadImage() {
    hLandscape1Image = static_cast<HBITMAP>(LoadImageW(NULL, L"img\\landscape1.bmp", IMAGE_BITMAP, 230, 150, LR_LOADFROMFILE));
    hGenerateImage = static_cast<HBITMAP>(LoadImageW(NULL, L"img\\generate.bmp", IMAGE_BITMAP, 100, 65, LR_LOADFROMFILE));
}