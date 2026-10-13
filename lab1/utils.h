#pragma once
#include <windows.h>

enum class wizard_nav {
    NEXT,
    BACK,
    FINISH,
    CANCEL
};

INT_PTR ShowDialogBox(HWND hWndParent, LPCWSTR title, short width, short height, DLGPROC dlgProc, LPARAM LParam = 0);