#include "module3.h"

#define IDC_M3_BACK 301

static INT_PTR CALLBACK Step2DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG: {
        HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

        HWND hText = CreateWindowExW(0, L"STATIC",
            L"Майстер: Крок 2 із 2.\nПідтвердіть виконання або поверніться назад.",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            15, 20, 280, 40, hDlg, NULL, GetModuleHandle(NULL), NULL);
        SendMessage(hText, WM_SETFONT, (WPARAM)hFont, TRUE);

        HWND hBtnBack = CreateWindowExW(0, L"BUTTON", L"< Назад",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            15, 75, 80, 28, hDlg, (HMENU)IDC_M3_BACK, GetModuleHandle(NULL), NULL);
        SendMessage(hBtnBack, WM_SETFONT, (WPARAM)hFont, TRUE);

        HWND hBtnOk = CreateWindowExW(0, L"BUTTON", L"Так",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            110, 75, 80, 28, hDlg, (HMENU)IDOK, GetModuleHandle(NULL), NULL);
        SendMessage(hBtnOk, WM_SETFONT, (WPARAM)hFont, TRUE);

        HWND hBtnCancel = CreateWindowExW(0, L"BUTTON", L"Відміна",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            205, 75, 80, 28, hDlg, (HMENU)IDCANCEL, GetModuleHandle(NULL), NULL);
        SendMessage(hBtnCancel, WM_SETFONT, (WPARAM)hFont, TRUE);

        return TRUE;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id == IDC_M3_BACK) {
            EndDialog(hDlg, static_cast<INT_PTR>(wizard_nav::BACK));
            return TRUE;
        }
        else if (id == IDOK) {
            EndDialog(hDlg, static_cast<INT_PTR>(wizard_nav::FINISH));
            return TRUE;
        }
        else if (id == IDCANCEL) {
            EndDialog(hDlg, static_cast<INT_PTR>(wizard_nav::CANCEL));
            return TRUE;
        }
        break;
    }
    }
    return FALSE;
}

wizard_nav ShowWizardStep2(HWND hWndParent) {
    INT_PTR res = ShowDialogBox(hWndParent, L"Робота 2 - Крок 2", 170, 75, Step2DlgProc);
    return static_cast<wizard_nav>(res);
}