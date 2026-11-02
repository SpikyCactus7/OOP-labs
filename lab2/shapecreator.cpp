#include "shapecreator.h"

ShapeCreator::ShapeCreator() {
    pse = nullptr;
}

ShapeCreator::~ShapeCreator() {
    delete pse;
    ShapeEditor::CleanUp();
}

void ShapeCreator::StartPointEditor(HWND hWnd) {
    delete pse;
    pse = new PointEditor();
    SetWindowTextW(hWnd, L"Поточний об'єкт: Крапка");
}

void ShapeCreator::StartLineEditor(HWND hWnd) {
    delete pse;
    pse = new LineEditor();
    SetWindowTextW(hWnd, L"Поточний об'єкт: Лінія");
}

void ShapeCreator::StartRectEditor(HWND hWnd) {
    delete pse;
    pse = new RectEditor();
    SetWindowTextW(hWnd, L"Поточний об'єкт: Прямокутник");
}

void ShapeCreator::StartEllipseEditor(HWND hWnd) {
    delete pse;
    pse = new EllipseEditor();
    SetWindowTextW(hWnd, L"Поточний об'єкт: Еліпс");
}

void ShapeCreator::OnLBdown(HWND hWnd) {
    if (pse) pse->OnLBdown(hWnd);
}

void ShapeCreator::OnLBup(HWND hWnd) {
    if (pse) pse->OnLBup(hWnd);
}

void ShapeCreator::OnMouseMove(HWND hWnd) {
    if (pse) pse->OnMouseMove(hWnd);
}

void ShapeCreator::OnPaint(HWND hWnd) {
    if (pse) {
        pse->OnPaint(hWnd);
    } else {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
}