#pragma once
#include <windows.h>
#include "editor.h"

class ShapeCreator {
private:
    ShapeEditor* pse = nullptr;
public:
    ShapeCreator();
    ~ShapeCreator();

    void StartPointEditor(HWND hWnd);
    void StartLineEditor(HWND hWnd);
    void StartRectEditor(HWND hWnd);
    void StartEllipseEditor(HWND hWnd);

    void OnLBdown(HWND hWnd);
    void OnLBup(HWND hWnd);
    void OnMouseMove(HWND hWnd);
    void OnPaint(HWND hWnd);
};