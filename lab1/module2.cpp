#include "module2.h"

#define IDC_M2_NEXT 201

static INT_PTR CALLBACK Step1DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG: {
        HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

        HWND hText = CreateWindowExW(0, L"STATIC",
            L"Майстер: Крок 1 із 2.\nНатисніть 'Далі >' для переходу до наступного вікна.",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            20, 20, 260, 40, hDlg, NULL, GetModuleHandle(NULL), NULL);
        SendMessage(hText, WM_SETFONT, (WPARAM)hFont, TRUE);

        HWND hBtnNext = CreateWindowExW(0, L"BUTTON", L"Далі >",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            45, 75, 95, 28, hDlg, (HMENU)IDC_M2_NEXT, GetModuleHandle(NULL), NULL);
        SendMessage(hBtnNext, WM_SETFONT, (WPARAM)hFont, TRUE);

        HWND hBtnCancel = CreateWindowExW(0, L"BUTTON", L"Відміна",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            160, 75, 95, 28, hDlg, (HMENU)IDCANCEL, GetModuleHandle(NULL), NULL);
        SendMessage(hBtnCancel, WM_SETFONT, (WPARAM)hFont, TRUE);

        return TRUE;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id == IDC_M2_NEXT) {
            EndDialog(hDlg, static_cast<INT_PTR>(wizard_nav::NEXT));
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

wizard_nav ShowWizardStep1(HWND hWndParent) {
    INT_PTR res = ShowDialogBox(hWndParent, L"Робота 2 - Крок 1", 160, 75, Step1DlgProc);
    return static_cast<wizard_nav>(res);
}