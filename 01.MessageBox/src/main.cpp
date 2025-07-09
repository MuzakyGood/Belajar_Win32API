#include <windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    MessageBoxA(NULL, "Hello, World!", "First GUI", MB_OK);
    return 0;
}