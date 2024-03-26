#include <stdlib.h>
#include <Windows.h>
#include <signal.h>

HHOOK hookHandle;
HMODULE wmDll;

// CTRL C INTERRUPTION
void ctrlc(int sig) {
    
    UnhookWindowsHookEx(hookHandle);
    exit(0);
}

int main() {

    // DLL loader
    wmDll = LoadLibraryW(L"wm_dll.dll");
    if(wmDll == NULL) {
        printf("error loading library: %d\n", GetLastError());
        exit(1);
    }

    FARPROC shellProc = GetProcAddress(wmDll, "ShellProc");
    if(shellProc == NULL) { 
        printf("error getting procedure addr: %d\n", GetLastError());
        exit(1);
    }

    // get events for created & destroyed windows - IF THREAD ID IS 0, AFFECTS ALL THREADS IN THE DESKTOP
    hookHandle = SetWindowsHookExW(WH_SHELL, shellProc, wmDll, 0);
    if(hookHandle == NULL) {
        printf("error setting hook: %d\n", GetLastError());
        exit(1);
    }

    // KB INTERRUPT
    signal(SIGINT, ctrlc);
    for(;;) {}
}
