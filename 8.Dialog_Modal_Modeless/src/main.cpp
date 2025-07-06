#include <iostream>
#include <windows.h>

#define MODAL_BUTTON 1
#define MODELESS_BUTTON 2
#define EXIT_MODAL_DIALOG_BUTTON 3
#define EXIT_MODELESS_DIALOG_BUTTON 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hMainWindow, hModelessWindow, hDescOutput;

void addControl(HWND);

// Deklarasi procedure untuk membuat Window Message Box Modal
void DialModalClass(HINSTANCE);
void drawDialogModal(HWND);

// Deklarasi procedure untuk membuat Window Message Box Modeless
void DialModelessClass(HINSTANCE);
void drawDialogModeless(HWND);

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

    DialModalClass(hInst);
    DialModelessClass(hInst);

    hMainWindow = CreateWindowW(L"firstWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessageW(&msg, NULL, static_cast<UINT>(NULL), static_cast<UINT>(NULL))) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

    std::string DescModal = "Dialog Modal message box adalah Dialog yang tidak mengizinkan interaksi dari Window Utama.";
    std::string DescModeless = "Dialog Modeless message box adalah Dialog yang mengizinkan interaksi dari Window Utama.";

    switch (msg) {

        case WM_COMMAND:
            switch (wp) {

                case MODAL_BUTTON:
                    drawDialogModal(hWnd);
                    MessageBeep(MB_ICONWARNING);

                    SetWindowTextA(hDescOutput, DescModal.c_str());
                break;

                case MODELESS_BUTTON:
                    drawDialogModeless(hWnd);
                    MessageBeep(MB_ICONWARNING);

                    SetWindowTextA(hDescOutput, DescModeless.c_str());
                break;

            }
        break;

        case WM_CREATE:
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
    CreateWindowW(L"STATIC", L"Dialog Modal and Modeless", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 35, 100, 50, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"EDIT", L"Test input here", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 110, 100, 24, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"BUTTON", L"Draw Modal Button", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 210, 159, 24, hWnd, reinterpret_cast<HMENU>(MODAL_BUTTON), NULL, NULL);
    CreateWindowW(L"BUTTON", L"Draw Modeless Button", WS_VISIBLE | WS_CHILD | WS_BORDER, 270, 210, 159, 24, hWnd, reinterpret_cast<HMENU>(MODELESS_BUTTON), NULL, NULL);

    CreateWindowW(L"STATIC", L"Description:", WS_VISIBLE | WS_CHILD, 70, 290, 100, 50, hWnd, NULL, NULL, NULL);
    hDescOutput = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 70, 310, 360, 100, hWnd, NULL, NULL, NULL);
}

/*
    Membuat window untuk Message Box.
    Membuat Message Box secara manual.
*/ 

LRESULT CALLBACK DialogModalProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        
        case WM_COMMAND:
            switch (wp) {

                case EXIT_MODAL_DIALOG_BUTTON:
                    EnableWindow(hModelessWindow, true);
                    EnableWindow(hMainWindow, true);
                    SetWindowTextW(hDescOutput, L"");
                    DestroyWindow(hWnd);
                break;

            }
        break;

        case WM_CLOSE:
            EnableWindow(hModelessWindow, true);
            EnableWindow(hMainWindow, true);
            SetWindowTextW(hDescOutput, L"");
            DestroyWindow(hWnd);
        break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return DefWindowProcW(hWnd, msg, wp, lp);
}

LRESULT CALLBACK DialogModelessProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

    switch (msg) {

        case WM_COMMAND: 
            switch (wp) {

                case EXIT_MODELESS_DIALOG_BUTTON:
                    SetWindowTextW(hDescOutput, L"");
                    DestroyWindow(hWnd);
                break;

            }
        break;

        case WM_CLOSE:
            SetWindowTextW(hDescOutput, L"");
            DestroyWindow(hWnd);
        break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return DefWindowProcW(hWnd, msg, wp, lp);
}

void DialModalClass(HINSTANCE hInst) {
    WNDCLASSW dialogModal = {0};
    dialogModal.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
    dialogModal.hCursor = LoadCursor(NULL, IDC_ARROW);
    dialogModal.hInstance = hInst;
    dialogModal.lpszClassName = L"myDialogModalClass";
    dialogModal.lpfnWndProc = DialogModalProcedure;

    RegisterClassW(&dialogModal);
}

void DialModelessClass(HINSTANCE hInst) {
    WNDCLASSW dialogModeless = {0};
    dialogModeless.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
    dialogModeless.hCursor = LoadCursor(NULL, IDC_ARROW);
    dialogModeless.hInstance = hInst;
    dialogModeless.lpszClassName = L"myDialogModelessClass";
    dialogModeless.lpfnWndProc = DialogModelessProcedure;

    RegisterClassW(&dialogModeless);
}

void drawDialogModal(HWND hWnd) {
    HWND hDialog = CreateWindowW(L"myDialogModalClass", L"Modal Message Box", WS_VISIBLE | WS_CAPTION | WS_SYSMENU, 200, 100, 200, 200, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"You cant press input in Window", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 50, 100, 50, hDialog, NULL, NULL, NULL);
    CreateWindowW(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 65, 115, 80, 28, hDialog, reinterpret_cast<HMENU>(EXIT_MODAL_DIALOG_BUTTON), NULL, NULL);

    EnableWindow(hMainWindow, false);
    EnableWindow(hModelessWindow, false);
}

void drawDialogModeless(HWND hWnd) {
    hModelessWindow = CreateWindowW(L"myDialogModelessClass", L"Modeless Message Box", WS_VISIBLE | WS_CAPTION | WS_SYSMENU, 200, 100, 200, 200, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"You can press input in Window", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 50, 100, 50, hModelessWindow, NULL, NULL, NULL);
    CreateWindowW(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 65, 115, 80, 28, hModelessWindow, reinterpret_cast<HMENU>(EXIT_MODELESS_DIALOG_BUTTON), NULL, NULL);
}
// ===========================================================