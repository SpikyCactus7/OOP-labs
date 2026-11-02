#include "editor.h"

Shape** ShapeEditor::pcshape = nullptr;
int ShapeEditor::count = 0;

ShapeEditor::ShapeEditor() {
    if (!pcshape) {
        pcshape = new Shape*[MY_SHAPE_ARRAY_SIZE];
        for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; ++i) {
            pcshape[i] = nullptr;
        }
    }
}

void ShapeEditor::CleanUp() {
    if (pcshape) {
        for (int i = 0; i < count; ++i) {
            delete pcshape[i];
        }
        delete[] pcshape;
        pcshape = nullptr;
        count = 0;
    }
}

void ShapeEditor::AddShape(Shape* s) {
    if (count < MY_SHAPE_ARRAY_SIZE) {
        pcshape[count++] = s;
    } else {
        delete s;
    }
}

void ShapeEditor::OnLBdown(HWND hWnd) {
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    x1 = x2 = pt.x;
    y1 = y2 = pt.y;
    isDrawing = true;
    SetCapture(hWnd);
}

void ShapeEditor::OnMouseMove(HWND hWnd) {
    if (!isDrawing) return;

    HDC hdc = GetDC(hWnd);
    SetROP2(hdc, R2_NOTXORPEN);
    
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    OnDrawRubber(hdc);

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    x2 = pt.x;
    y2 = pt.y;

    OnDrawRubber(hdc);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
    ReleaseDC(hWnd, hdc);
}

void ShapeEditor::OnLBup(HWND hWnd) {
    if (isDrawing) {
        isDrawing = false;
        ReleaseCapture();
    }
}

void ShapeEditor::OnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    for (int i = 0; i < count; ++i) {
        if (pcshape[i]) {
            pcshape[i]->Show(hdc);
        }
    }

    EndPaint(hWnd, &ps);
}

void PointEditor::OnDrawRubber(HDC hdc) {}

void PointEditor::OnLBup(HWND hWnd) {
    if (!isDrawing) return;
    ShapeEditor::OnLBup(hWnd);

    Shape* s = new PointShape();
    s->Set(x1, y1, x2, y2);
    AddShape(s);
    InvalidateRect(hWnd, NULL, TRUE);
}

void LineEditor::OnDrawRubber(HDC hdc) {
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

void LineEditor::OnLBup(HWND hWnd) {
    if (!isDrawing) return;
    ShapeEditor::OnLBup(hWnd);

    Shape* s = new LineShape();
    s->Set(x1, y1, x2, y2);
    AddShape(s);
    InvalidateRect(hWnd, NULL, TRUE);
}

void RectEditor::OnDrawRubber(HDC hdc) {
    long left = 2 * x1 - x2;
    long top = 2 * y1 - y2;
    Rectangle(hdc, left, top, x2, y2);
}

void RectEditor::OnLBup(HWND hWnd) {
    if (!isDrawing) return;
    ShapeEditor::OnLBup(hWnd);

    Shape* s = new RectShape();
    s->Set(x1, y1, x2, y2);
    AddShape(s);
    InvalidateRect(hWnd, NULL, TRUE);
}

void EllipseEditor::OnDrawRubber(HDC hdc) {
    Ellipse(hdc, x1, y1, x2, y2);
}

void EllipseEditor::OnLBup(HWND hWnd) {
    if (!isDrawing) return;
    ShapeEditor::OnLBup(hWnd);

    Shape* s = new EllipseShape();
    s->Set(x1, y1, x2, y2);
    AddShape(s);
    InvalidateRect(hWnd, NULL, TRUE);
}