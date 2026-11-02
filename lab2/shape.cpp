#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2) {
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
}

void PointShape::Show(HDC hdc) {
    SetPixel(hdc, xs1, ys1, RGB(0, 0, 0));
    SetPixel(hdc, xs1 + 1, ys1, RGB(0, 0, 0));
    SetPixel(hdc, xs1, ys1 + 1, RGB(0, 0, 0));
    SetPixel(hdc, xs1 + 1, ys1 + 1, RGB(0, 0, 0));
}

void LineShape::Show(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, xs1, ys1, NULL);
    LineTo(hdc, xs2, ys2);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}

void RectShape::Show(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    long left = 2 * xs1 - xs2;
    long top = 2 * ys1 - ys2;
    long right = xs2;
    long bottom = ys2;

    Rectangle(hdc, left, top, right, bottom);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}

void EllipseShape::Show(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 191, 255));

    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    Ellipse(hdc, xs1, ys1, xs2, ys2);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPen);
}