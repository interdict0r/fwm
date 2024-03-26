#include <stdlib.h>
#include <Windows.h>
#include <signal.h>

HHOOK hookHandle;
// CTRL C INTERRUPTION
void ctrlc(int sig) {

    UnhookWindowsHookEx(hookHandle);
    exit(0);
}

int main() {

    // DLL loader
    HMODULE wmDll = LoadLibraryW(L"wm_dll");
    FARPROC shellProc = GetProcAddress(wmDll, "ShellProc"); 
    // get events for created & destroyed windows - IF THREAD ID IS 0, AFFECTS ALL THREADS IN THE DESKTOP
    hookHandle = SetWindowsHookExW(WH_SHELL, shellProc, wmDll, 0);

    // KB INTERRUPT
    signal(SIGINT, ctrlc);
    for(;;) {}
}
