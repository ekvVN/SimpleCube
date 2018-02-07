//
// Created by root on 06.02.18.
//

#ifndef QTGUIEXAMPLE_PRIMITIVEPAINTER_H
#define QTGUIEXAMPLE_PRIMITIVEPAINTER_H

#include <vector>

#include "Image.h"
#include "geometry.h"

/**
 * Класс для отрисовки примитивов
 * draw_*() - отрисовка контура
 * fill_*() - отрисовка с заливкой
 */
class PrimitivePainter
{
public:
    //--------------
    // 2D
    //--------------

    void draw_line(Image &image, int x0, int y0, int x1, int y1, Pixel color);
    void draw_line(Image &image, std::array<Vec2i, 2> p, Pixel color);
    void draw_triangle(Image &image, std::array<Vec2i, 3> p, Pixel color);
    void fill_triangle(Image &image, std::array<Vec2i, 3> p, Pixel color);

    //--------------
    // 3D
    //--------------

    // с использованием z-буфера для отсечения ненужных пикселей
    void fill_triangle(Image &image, std::array<Vec3i, 3> p, Pixel color, std::vector<int> &zbuffer);
    void fill_triangle(Image &image, std::array<Vec3i, 3> p, std::array<float, 3> ity, std::vector<int> &zbuffer);


    // Соритировка вершин по высоте
    template <typename T>
    bool sort_verts(std::array<T, 3> &p);
};


#endif //QTGUIEXAMPLE_PRIMITIVEPAINTER_H
