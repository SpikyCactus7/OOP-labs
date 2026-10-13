#include <windows.h>
#include <cwchar>
#include "module1.h"
#include "module2.h"
#include "module3.h"
#include "utils.h"

#define IDM_WORK1 9001
#define IDM_WORK2 9002

static bool g_Executed1 = false;
static int  g_Value1 = 0;
static bool g_Completed2 = false;

static void RunWork2Wizard(HWND hWnd) {
    int currentStep = 1;

    while (currentStep != 0) {
        if (currentStep == 1) {
            wizard_nav res = ShowWizardStep1(hWnd);
            if (res == wizard_nav::NEXT) {
                currentStep = 2;
            } else {
                currentStep = 0;
            }
        }
        else if (currentStep == 2) {
            wizard_nav res = ShowWizardStep2(hWnd);
            if (res == wizard_nav::BACK) {
                currentStep = 1;
            } else if (res == wizard_nav::FINISH) {
                g_Completed2 = true;
                currentStep = 0;
                InvalidateRect(hWnd, NULL, TRUE);
            } else {
                currentStep = 0;
            }
        }
    }
}

static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDM_WORK1: {
            int selectedNum = 0;
            if (ShowDialog1(hWnd, &selectedNum)) {
                g_Value1 = selectedNum;
                g_Executed1 = true;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        case IDM_WORK2: {
            RunWork2Wizard(hWnd);
            break;
        }
        }
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        WCHAR text1[128];
        if (g_Executed1) {
            swprintf_s(text1, L"Результат роботи 1: %d", g_Value1);
        } else {
            wcscpy_s(text1, L"Результат роботи 1: (не виконано)");
        }

        WCHAR text2[128];
        if (g_Completed2) {
            wcscpy_s(text2, L"Результат роботи 2: Завершено (крок 2 підтверджено)");
        } else {
            wcscpy_s(text2, L"Результат роботи 2: (не виконано)");
        }

        TextOutW(hdc, 25, 30, L"Лабораторна робота №1 (B1 = 1, B2 = 2)", 38);
        TextOutW(hdc, 25, 70, text1, static_cast<int>(wcslen(text1)));
        TextOutW(hdc, 25, 100, text2, static_cast<int>(wcslen(text2)));

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Lab1MainWindowClass";

    WNDCLASSEXW wc = { sizeof(WNDCLASSEXW) };
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassExW(&wc);

    HMENU hMenuBar = CreateMenu();
    AppendMenuW(hMenuBar, MF_STRING, IDM_WORK1, L"Робота1");
    AppendMenuW(hMenuBar, MF_STRING, IDM_WORK2, L"Робота2");

    HWND hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Лабораторна робота №1",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 560, 320,
        NULL,
        hMenuBar,
        hInstance,
        NULL
    );

    if (!hWnd) return 0;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}