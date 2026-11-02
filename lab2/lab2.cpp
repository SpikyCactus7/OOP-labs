#include <windows.h>
#include "shapecreator.h"

#define IDM_EXIT     9001
#define IDM_POINT    9002
#define IDM_LINE     9003
#define IDM_RECT     9004
#define IDM_ELLIPSE  9005
#define IDM_ABOUT    9006

static ShapeCreator g_Editor;
static HMENU g_hObjMenu = nullptr;

static void SetSelectedObject(UINT cmId) {
    CheckMenuRadioItem(g_hObjMenu, IDM_POINT, IDM_ELLIPSE, cmId, MF_BYCOMMAND);
}

static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        g_Editor.StartPointEditor(hWnd);
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDM_POINT:
            SetSelectedObject(IDM_POINT);
            g_Editor.StartPointEditor(hWnd);
            break;
        case IDM_LINE:
            SetSelectedObject(IDM_LINE);
            g_Editor.StartLineEditor(hWnd);
            break;
        case IDM_RECT:
            SetSelectedObject(IDM_RECT);
            g_Editor.StartRectEditor(hWnd);
            break;
        case IDM_ELLIPSE:
            SetSelectedObject(IDM_ELLIPSE);
            g_Editor.StartEllipseEditor(hWnd);
            break;
        case IDM_ABOUT:
            MessageBoxW(hWnd, L"Лабораторна робота №2\nВаріант 9", L"Довідка", MB_OK | MB_ICONINFORMATION);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
        return 0;

    case WM_LBUTTONDOWN:
        g_Editor.OnLBdown(hWnd);
        return 0;

    case WM_LBUTTONUP:
        g_Editor.OnLBup(hWnd);
        return 0;

    case WM_MOUSEMOVE:
        g_Editor.OnMouseMove(hWnd);
        return 0;

    case WM_PAINT:
        g_Editor.OnPaint(hWnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Lab2WindowClass";

    WNDCLASSEXW wc = { sizeof(WNDCLASSEXW) };
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassExW(&wc);

    HMENU hMenuBar = CreateMenu();
    HMENU hFileMenu = CreatePopupMenu();
    g_hObjMenu = CreatePopupMenu();
    HMENU hHelpMenu = CreatePopupMenu();

    AppendMenuW(hFileMenu, MF_STRING, IDM_EXIT, L"Вихід");

    AppendMenuW(g_hObjMenu, MF_STRING | MFT_RADIOCHECK, IDM_POINT, L"Крапка");
    AppendMenuW(g_hObjMenu, MF_STRING | MFT_RADIOCHECK, IDM_LINE, L"Лінія");
    AppendMenuW(g_hObjMenu, MF_STRING | MFT_RADIOCHECK, IDM_RECT, L"Прямокутник");
    AppendMenuW(g_hObjMenu, MF_STRING | MFT_RADIOCHECK, IDM_ELLIPSE, L"Еліпс");
    SetSelectedObject(IDM_POINT);

    AppendMenuW(hHelpMenu, MF_STRING, IDM_ABOUT, L"Про програму");

    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"Файл");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)g_hObjMenu, L"Об'єкти");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hHelpMenu, L"Довідка");

    HWND hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Лабораторна робота №2",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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