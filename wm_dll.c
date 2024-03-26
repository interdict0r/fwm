#include <stdlib.h>
#include <Windows.h>

__declspec(dllexport) LRESULT CALLBACK ShellProc(int code, WPARAM wparam, LPARAM lparam) {

    if(code == HSHELL_WINDOWCREATED || code == HSHELL_WINDOWDESTROYED) {
        // null parameter for whole parent window
        TileWindows(NULL, MDITILE_VERTICAL, NULL, NULL, NULL);
    }

    return CallNextHookEx(NULL, code, wparam, lparam);
}