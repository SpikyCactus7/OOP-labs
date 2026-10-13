#include "utils.h"
#include <vector>

INT_PTR ShowDialogBox(HWND hWndParent, LPCWSTR title, short width, short height, DLGPROC dlgProc, LPARAM LParam) {
    std::vector<byte> buffer(sizeof(DLGTEMPLATE) + 512, 0);
    LPDLGTEMPLATE pDlg = reinterpret_cast<LPDLGTEMPLATE>(buffer.data());
    pDlg->style = WS_POPUP | WS_CAPTION | WS_SYSMENU | DS_MODALFRAME | DS_CENTER;
    pDlg->dwExtendedStyle = 0;
    pDlg->cdit = 0;
    pDlg->x = 0;
    pDlg->y = 0;
    pDlg->cx = width;
    pDlg->cy = height;

    LPWORD p = reinterpret_cast<LPWORD>(pDlg + 1);
    *p++ = 0;
    *p++ = 0;
    LPWSTR pTitle = reinterpret_cast<LPWSTR>(p);
    wcscpy_s(pTitle, 128, title);
    return DialogBoxIndirectParam(GetModuleHandle(NULL), pDlg, hWndParent, dlgProc, LParam);
}