#pragma once
#include <windows.h>
#include "shape.h"

const int MY_SHAPE_ARRAY_SIZE = 109;

class Editor {
public:
    virtual ~Editor() = default;
    virtual void OnLBdown(HWND hWnd) = 0;
    virtual void OnLBup(HWND hWnd) = 0;
    virtual void OnMouseMove(HWND hWnd) = 0;
    virtual void OnPaint(HWND hWnd) = 0;
};

class ShapeEditor : public Editor {
protected:
    long x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    bool isDrawing = false;

    static Shape** pcshape;
    static int count;

    void AddShape(Shape* s);
public:
    ShapeEditor();
    virtual ~ShapeEditor() = default;

    static void CleanUp();

    void OnLBdown(HWND hWnd) override;
    void OnLBup(HWND hWnd) override;
    void OnMouseMove(HWND hWnd) override;
    void OnPaint(HWND hWnd) override;

    virtual void OnDrawRubber(HDC hdc) = 0;
};

class PointEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd) override;
    void OnDrawRubber(HDC hdc) override;
};

class LineEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd) override;
    void OnDrawRubber(HDC hdc) override;
};

class RectEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd) override;
    void OnDrawRubber(HDC hdc) override;
};

class EllipseEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd) override;
    void OnDrawRubber(HDC hdc) override;
};