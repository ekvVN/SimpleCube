//
// Created by root on 30.01.18.
//

#ifndef QTGUIEXAMPLE_MYPAINTER_H
#define QTGUIEXAMPLE_MYPAINTER_H

#include <cmath>
#include <utility>
#include <limits>
#include <memory>

#include "model.h"
#include "Matrix3x3.h"
#include "PrimitivePainter.h"
#include "Image.h"
#include "ViewMatrix.h"

class MyPainter
{
    PrimitivePainter _painter;
    Model *_model;
    std::shared_ptr<Model> _testModel;  // Тестовая модель с нормалями для заливки
    std::vector<int> _zbuffer;
    Vec3f _light_dir; // направлени света

    const int depth  = 255;

public:
    std::shared_ptr<ViewMatrix> _viewMatrix;

public:
    MyPainter();

    // Установка рисуемой модели
    void SetModel(Model *model);
    void setLightDir(Vec3f light_dir);

    /*
     * Нарисовать что-то :)
     * pixs - указатель на массив пикселей
     * width - ширина изображения
     * height - выоста изображения
     */
    void DrawCube(Pixel *pixs, int width, int height);

private:
    // Отрисовка контуров треугольников модели
    void draw_model(Model *model, Image &image, Pixel color);

    // Заливка треугольников модели
    void fill_model(Model *model, Image &image, Pixel color);

    // Заливка треугольников модели рандомным цветом
    void random_fill_model(Model *model, Image &image);

    // Заливка треугольников модели с учетом нормалей и направления света
    void fill_model_with_normal(Model *model, Image &image);

    // Заливка треугольников модели с учетом нормалей и направления света
    // и с использованием z-буфера для отсечения ненужных пикселей
    void fill_model_with_z_buffer(Model *model, Image &image);

    // вершина треугольника
    struct triangleVertex
    {
        // координаты вершины
        Vec3i screen_v;
        Vec3f world_v;

        // вектор нормали вершины
        Vec3f n;
    };

    // расчет интенсивности между вектором нормали и вектором света
    double CalcIntensity(Vec3f n, Vec3f light_dir);

    // Заливка треугольника методом Гуро
    // Аналог fill_triangle - с использованием z-буфера для отсечения ненужных пикселей
    void fill_triangle_guro(triangleVertex t[3], Image &image, std::vector<int> &zbuffer);

    // Заливка треугольника методом Гуро
    // Аналог fill_triangle - с использованием z-буфера для отсечения ненужных пикселей
    // TODO неееееее раааботаает :)
    void fill_triangle_guro2(triangleVertex t[3], Image &image, std::vector<int> &zbuffer);

    // Аналог fill_model_with_z_buffer
    // Заливка методом Гуро
    void fill_model_with_z_buffer2(Model *model, Image &image);

    void DrawModel3(Image& image, Model *model);

    void clear_zbuffer(int length);
};


#endif //QTGUIEXAMPLE_MYPAINTER_H
