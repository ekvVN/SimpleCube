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

class MyPainter
{
    PrimitivePainter _painter;
    Model *_model;
    std::shared_ptr<Model> _testModel;  // Тестовая модель с нормалями для заливки
    std::vector<int> _zbuffer;

    const int depth  = 255;

public:
    MyPainter();

    // Установка рисуемой модели
    void SetModel(Model *model);

    /*
     * Нарисовать что-то :)
     * pixs - указатель на массив пикселей
     * width - ширина изображения
     * height - выоста изображения
     */
    void DrawCube(Pixel *pixs, int width, int height);

private:

    void DrawModel3(Image& image, Model *model)
    {
        int width = image.width();
        int height = image.height();
        const int depth  = 255;

        Vec3f light_dir = Vec3f(1,-1,1).normalize();
        Vec3f eye(1,1,3);
        Vec3f center(0,0,0);


        // Поскольку у нас экран двумерный, то z-буфер тоже должен быть двумерным:
        auto size = width*height;
        if (_zbuffer.size() != size)
            _zbuffer.resize(size);

        for (int i=0; i<width*height; i++) {
            _zbuffer[i] = std::numeric_limits<int>::min();
        }

// draw the model
        auto modelView  = Matrix::lookat(eye, center, Vec3f(0,1,0));
        auto projection = Matrix::identity(4);
        auto viewPort   = Matrix::viewport(width/8, height/8, width*3/4, height*3/4);
        projection[3][2] = -1.f/(eye-center).norm();

        Matrix m = (viewPort*projection*modelView);

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            std::array<Vec3i, 3> screen_coords;
            std::array<Vec3f, 3> world_coords;
            std::array<float, 3> intensity;
            for (int j=0; j<3; j++) {
                Vec3f v = model->vert(face[j].idxVertex);
                screen_coords[j] =  Vec3f(m*Matrix(v));
                world_coords[j]  = v;
                intensity[j] = model->normal(face[j].idxNormal) * light_dir;
            }
            _painter.fill_triangle(image, screen_coords, intensity, _zbuffer);
        }
    }


    // Отрисовка контуров треугольников модели
    void draw_model(Model *model, Image &image, Pixel color);

    // Заливка треугольников модели
    void fill_model(Model *model, Image &image, Pixel color);

    // Заливка треугольников модели рандомным цветом
    void random_fill_model(Model *model, Image &image);

    // Заливка треугольников модели с учетом нормалей и направления света
    // light_dir - вектор направление света
    void fill_model_with_normal(Model *model, Image &image, Vec3f &light_dir);

    // Заливка треугольников модели с учетом нормалей и направления света
    // и с использованием z-буфера для отсечения ненужных пикселей
    // light_dir - вектор направление света
    void fill_model_with_z_buffer(Model *model, Image &image, Vec3f &light_dir);

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
    void fill_triangle_guro(triangleVertex t[3], Image &image, Vec3f &light_dir, std::vector<int> &zbuffer);

    // Заливка треугольника методом Гуро
    // Аналог fill_triangle - с использованием z-буфера для отсечения ненужных пикселей
    // TODO неееееее раааботаает :)
    void fill_triangle_guro2(triangleVertex t[3], Image &image, Vec3f &light_dir, std::vector<int> &zbuffer);

    // Аналог fill_model_with_z_buffer
    // Заливка методом Гуро
    void fill_model_with_z_buffer2(Model *model, Image &image, Vec3f &light_dir);
};


#endif //QTGUIEXAMPLE_MYPAINTER_H
