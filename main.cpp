#include <iostream>

#include "Casino.h"
#include "windows.h"
#include <io.h>
#include <fcntl.h>

void setupConsole() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

int main() {
    setupConsole();

    Casino casino = Casino();

    casino.run();
}