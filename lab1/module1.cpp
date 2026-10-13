#include "module1.h"
#include "utils.h"
#include <cwchar>

#define IDC_M1_SCROLLBAR 101
#define IDC_M1_STATIC    102

struct Data1 {
    int value;
    int* pOutValue;
};

static INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG: {
        SetWindowLongPtr(hDlg, DWLP_USER, lParam);
        Data1* data = reinterpret_cast<Data1*>(lParam);
        HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

        HWND hStatic = CreateWindowExW(0, L"STATIC", L"Вибране число: 50",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            20, 15, 260, 20, hDlg, (HMENU)IDC_M1_STATIC, GetModuleHandle(NULL), NULL);
        SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);

        HWND hScroll = CreateWindowExW(0, L"SCROLLBAR", NULL,
            WS_CHILD | WS_VISIBLE | SBS_HORZ,
            20, 45, 260, 22, hDlg, (HMENU)IDC_M1_SCROLLBAR, GetModuleHandle(NULL), NULL);

        SCROLLINFO si = { sizeof(SCROLLINFO) };
        si.fMask = SIF_RANGE | SIF_POS | SIF_PAGE;
        si.nMin = 1;
        si.nMax = 109;
        si.nPage = 10;
        si.nPos = data->value;
        SetScrollInfo(hScroll, SB_CTL, &si, TRUE);

        HWND hBtnOk = CreateWindowExW(0, L"BUTTON", L"Так",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            45, 85, 90, 28, hDlg, (HMENU)IDOK, GetModuleHandle(NULL), NULL);
        SendMessage(hBtnOk, WM_SETFONT, (WPARAM)hFont, TRUE);

        HWND hBtnCancel = CreateWindowExW(0, L"BUTTON", L"Відміна",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            165, 85, 90, 28, hDlg, (HMENU)IDCANCEL, GetModuleHandle(NULL), NULL);
        SendMessage(hBtnCancel, WM_SETFONT, (WPARAM)hFont, TRUE);

        return TRUE;
    }

    case WM_HSCROLL: {
        Data1* data = reinterpret_cast<Data1*>(GetWindowLongPtr(hDlg, DWLP_USER));
        HWND hScroll = (HWND)lParam;
        SCROLLINFO si = { sizeof(SCROLLINFO), SIF_ALL };
        GetScrollInfo(hScroll, SB_CTL, &si);

        int curPos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_LINELEFT:      curPos -= 1; break;
        case SB_LINERIGHT:     curPos += 1; break;
        case SB_PAGELEFT:      curPos -= 10; break;
        case SB_PAGERIGHT:     curPos += 10; break;
        case SB_THUMBTRACK:
        case SB_THUMBPOSITION: curPos = HIWORD(wParam); break;
        }

        if (curPos < 1) curPos = 1;
        if (curPos > 100) curPos = 100;
        si.fMask = SIF_POS;
        si.nPos = curPos;
        SetScrollInfo(hScroll, SB_CTL, &si, TRUE);
        data->value = curPos;

        WCHAR buf[64];
        swprintf_s(buf, L"Вибране число: %d", curPos);
        SetDlgItemTextW(hDlg, IDC_M1_STATIC, buf);
        return TRUE;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);
        Data1* data = reinterpret_cast<Data1*>(GetWindowLongPtr(hDlg, DWLP_USER));

        if (id == IDOK) {
            if (data && data->pOutValue) {
                *(data->pOutValue) = data->value;
            }
            EndDialog(hDlg, IDOK);
            return TRUE;
        }
        else if (id == IDCANCEL) {
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    }
    return FALSE;
}

bool ShowDialog1(HWND hWndParent, int* outValue) {
    Data1 data;
    data.value = 50;
    data.pOutValue = outValue;

    INT_PTR res = ShowDialogBox(hWndParent, L"Робота 1 - Вибір числа", 160, 85, DlgProc1, (LPARAM)&data);
    return (res == IDOK);
}