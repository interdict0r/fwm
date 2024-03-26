#include <stdlib.h>
#include <Windows.h>

__declspec(dllexport) LRESULT CALLBACK ShellProc(int code, WPARAM wparam, LPARAM lparam) {

    static int windowCount = 0;

    if(code == HSHELL_WINDOWCREATED || code == HSHELL_WINDOWDESTROYED) {

        HWND desktop = GetDesktopWindow();
        HWND child = GetWindow(desktop, GW_CHILD);
        int newWindowCount = 0;

        while(child) {

            newWindowCount += !IsIconic(child);
            child = GetWindow(child, GW_HWNDNEXT);
        }

        if(newWindowCount > windowCount) {
            if(newWindowCount > 1) {
                // null parameters for whole parent window
                TileWindows(NULL, MDITILE_VERTICAL, NULL, NULL, NULL);
            }

            windowCount = newWindowCount;
        }
    }

    return CallNextHookEx(NULL, code, wparam, lparam);
}
