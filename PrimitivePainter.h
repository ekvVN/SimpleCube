//
// Created by root on 06.02.18.
//

#ifndef QTGUIEXAMPLE_PRIMITIVEPAINTER_H
#define QTGUIEXAMPLE_PRIMITIVEPAINTER_H

#include <vector>

#include "Image.h"
#include "geometry.h"

class PrimitivePainter
{
public:
    // Отрисовка линии
    void draw_line(Image &image, int x0, int y0, int x1, int y1, Pixel color);
    void draw_line(Image &image, Vec2i p0, Vec2i p1, Pixel color);

    // Отрисовка контура треугольника
    void draw_triangle(Image &image, Vec2i t0, Vec2i t1, Vec2i t2, Pixel color);

    // Заливка треугольника
    void fill_triangle(Image &image, Vec2i t0, Vec2i t1, Vec2i t2, Pixel color);
    // с использованием z-буфера для отсечения ненужных пикселей
    void fill_triangle(Image &image, Vec3i t0, Vec3i t1, Vec3i t2, Pixel color, std::vector<int> &zbuffer);
};


#endif //QTGUIEXAMPLE_PRIMITIVEPAINTER_H
