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

    MyPainter()
        : _model(nullptr)
    {
    }

    void SetModel(Model *model)
    {
        _model = model;
    }

    void RotateModel(Matrix3x3<float> m)
    {
        for (int i = 0; i < _model->nverts(); i++)
        {
            Vec3f v = _model->vert(i);
            Vec3f resV = v * m;
            _model->set_vert(i, resV);
        }

        for (int i = 0; i < _model->nnormals(); i++)
        {
            Vec3f n = _model->normal(i);
            Vec3f resN = n * m;
            _model->set_normal(i, resN);
        }
    }

    Matrix viewport(int x, int y, int w, int h) {
        Matrix m = Matrix::identity(4);
        m[0][3] = x+w/2.f;
        m[1][3] = y+h/2.f;
        m[2][3] = depth/2.f;

        m[0][0] = w/2.f;
        m[1][1] = h/2.f;
        m[2][2] = depth/2.f;
        return m;
    }

    Matrix lookat(Vec3f eye, Vec3f center, Vec3f up) {
        Vec3f z = (eye-center).normalize();
        Vec3f x = (up^z).normalize();
        Vec3f y = (z^x).normalize();
        Matrix res = Matrix::identity(4);
        for (int i=0; i<3; i++) {
            res[0][i] = x[i];
            res[1][i] = y[i];
            res[2][i] = z[i];
            res[i][3] = -center[i];
        }
        return res;
    }



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
        Matrix ModelView  = lookat(eye, center, Vec3f(0,1,0));
        Matrix Projection = Matrix::identity(4);
        Matrix ViewPort   = viewport(width/8, height/8, width*3/4, height*3/4);
        Projection[3][2] = -1.f/(eye-center).norm();

//        std::cerr << ModelView << std::endl;
//        std::cerr << Projection << std::endl;
//        std::cerr << ViewPort << std::endl;
        Matrix z = (ViewPort*Projection*ModelView);
//        std::cerr << z << std::endl;

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            Vec3i screen_coords[3];
            Vec3f world_coords[3];
            float intensity[3];
            for (int j=0; j<3; j++) {
                Vec3f v = model->vert(face[j].idxVertex);
                screen_coords[j] =  Vec3f(ViewPort*Projection*ModelView*Matrix(v));
                world_coords[j]  = v;
                intensity[j] = model->normal(face[j].idxNormal) * light_dir;
            }
            _painter.fill_triangle(image, screen_coords[0], screen_coords[1], screen_coords[2], intensity[0], intensity[1], intensity[2], _zbuffer);
        }
    }

    /*
     * Нарисовать что-то :)
     * pixs - указатель на массив пикселей
     * width - ширина изображения
     * height - выоста изображения
     */
    void DrawCube(Pixel *pixs, int width, int height)
    {
        Image image(pixs, width, height);

        Pixel white = {0xFF, 0xFF, 0xFF, 0xFF};
        Pixel blue =  {0xFF, 0x00, 0x00, 0xFF};
        Pixel green = {0x00, 0xFF, 0x00, 0xFF};
        Pixel red =   {0x00, 0x00, 0xFF, 0xFF};

        if(_model)
        {
            // 1. Отрисовка контуров модели
//            draw_model(_model, image, white);

            // 2.1. Заливка треугольников модели
//            fill_model(_model, image, green);

            // 2.2 Заливка треугольников модели рандомным цветом
//            random_fill_model(_model, image);

            Vec3f light_dir= Vec3f(1,-1,1).normalize();
            Vec3f eye(1,1,3);
            Vec3f center(0,0,0);
            DrawModel3(image, _model);
//            DrawModel3(image, _model, light_dir, eye, center);



            // 2.3 Заливка треугольников модели с учетом нормалей и направления света
//            fill_model_with_normal(_model, image, light_dir);

            // 3.1 Заливка треугольников модели с учетом нормалей и направления света
            // и с использованием z-буфера для отсечения ненужных пикселей
//            fill_model_with_z_buffer(_model, image, light_dir);

            // Аналог fill_model_with_z_buffer
            // Заливка методом Гуро
//            Vec3f light_dir_guro(0,0,1);    // вектор направления света (в обратную сторону сделал)
//            fill_model_with_z_buffer2(_model, image, light_dir);
        }
        else
        {
            // 1.1 Отрисовка линий
//            _painter.draw_line(image, 13, 20, 80, 40, white);
//            _painter.draw_line(image, 20, 13, 40, 80, blue);
//            _painter.draw_line(image, 80, 40, 13, 20, blue);

            // 1.2 Отрисовка линий метеодом с перегрузкой для вершин
            _painter.draw_line(image, Vec2i(13, 20), Vec2i(80, 40), white);
            _painter.draw_line(image, Vec2i(20, 13), Vec2i(40, 80), blue);
            _painter.draw_line(image, Vec2i(80, 40), Vec2i(13, 20), blue);

            // 2.1 Отрисовка контуров треугольников
            Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
            Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
            Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

            _painter.draw_triangle(image, t0[0], t0[1], t0[2], red);
            _painter.draw_triangle(image, t1[0], t1[1], t1[2], green);
            _painter.draw_triangle(image, t2[0], t2[1], t2[2], blue);

            // 2.1 Заливка треугольников
            Vec2i fill_t0[3] = {Vec2i(210, 70),   Vec2i(250, 160),  Vec2i(270, 80)};
            Vec2i fill_t1[3] = {Vec2i(380, 50),  Vec2i(350, 1),   Vec2i(270, 180)};
            Vec2i fill_t2[3] = {Vec2i(380, 150), Vec2i(320, 160), Vec2i(330, 180)};

            _painter.fill_triangle(image, fill_t0[0], fill_t0[1], fill_t0[2], red);
            _painter.fill_triangle(image, fill_t1[0], fill_t1[1], fill_t1[2], green);
            _painter.fill_triangle(image, fill_t2[0], fill_t2[1], fill_t2[2], blue);

            // Тестовая модель с нормалями для заливки
            if(!_testModel)
            {
                std::vector<Vec3f> verts = {
                    Vec3f(0.5, -0.5, 0.2),
                    Vec3f(0.5,  0.5, 0.2),
                    Vec3f(0.3, -0.5, 0.3),
                    Vec3f(0.3,  0.5, 0.3),
                    Vec3f(0.2, -0.5, 0.5),
                    Vec3f(0.2,  0.5, 0.5),
                };
                std::vector<Vec3f> normals = {
                    Vec3f(0.5, 0.0, 0.8),
                    Vec3f(0.8, 0.0, 0.5),
                };

                std::vector<std::vector<faceVertex>> faces = {
                    { {5, 0, 0}, {4, 0, 0}, {3, 0, 0} },
                    { {2, 0, 0}, {3, 0, 0}, {4, 0, 0} },
                    { {1, 0, 1}, {3, 0, 1}, {2, 0, 1} },
                    { {0, 0, 1}, {1, 0, 1}, {2, 0, 1} },
                };
                _testModel = std::make_shared<Model>(verts, normals, faces);
            }
            Vec3f light_dir(0,0,-1);    // вектор направления света
//            random_fill_model(_testModel.get(), image);
            fill_model_with_z_buffer(_testModel.get(), image, light_dir);
        }
    }

    // Отрисовка контуров треугольников модели
    void draw_model(Model *model, Image &image, Pixel color)
    {
        int width = image.width();
        int height = image.height();

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            for (int j=0; j<3; j++) {
                Vec3f v0 = model->vert(face[j].idxVertex);
                Vec3f v1 = model->vert(face[(j+1)%3].idxVertex);
                int x0 = (v0.x+1.)*width/2.;
                int y0 = (v0.y+1.)*height/2.;
                int x1 = (v1.x+1.)*width/2.;
                int y1 = (v1.y+1.)*height/2.;
                _painter.draw_line(image, x0, y0, x1, y1, color);
            }
        }
    }

    // Заливка треугольников модели
    void fill_model(Model *model, Image &image, Pixel color)
    {
        int width = image.width();
        int height = image.height();

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            Vec2i screen_coords[3];
            for (int j=0; j<3; j++) {
                Vec3f world_coords = model->vert(face[j].idxVertex);
                screen_coords[j] = Vec2i((world_coords.x+1.)*width/2., (world_coords.y+1.)*height/2.);
            }
            _painter.fill_triangle(image, screen_coords[0], screen_coords[1], screen_coords[2], color);
        }
    }

    // Заливка треугольников модели рандомным цветом
    void random_fill_model(Model *model, Image &image)
    {
        int width = image.width();
        int height = image.height();

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            Vec2i screen_coords[3];
            for (int j=0; j<3; j++) {
                Vec3f world_coords = model->vert(face[j].idxVertex);
                screen_coords[j] = Vec2i((world_coords.x+1.)*width/2., (world_coords.y+1.)*height/2.);
            }
            Pixel randColor = {rand()%255, rand()%255, rand()%255, 255};
            _painter.fill_triangle(image, screen_coords[0], screen_coords[1], screen_coords[2], randColor);
        }
    }

    // Заливка треугольников модели с учетом нормалей и направления света
    // light_dir - вектор направление света
    void fill_model_with_normal(Model *model, Image &image, Vec3f &light_dir)
    {
        int width = image.width();
        int height = image.height();

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            Vec2i screen_coords[3];
            Vec3f world_coords[3];
            for (int j=0; j<3; j++) {
                Vec3f v = model->vert(face[j].idxVertex);
                screen_coords[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.);
                world_coords[j]  = v;
            }
            Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
            n.normalize();
            float intensity = n*light_dir;
            if (intensity>0) {
                Pixel color = {intensity*255, intensity*255, intensity*255, 255};
                _painter.fill_triangle(image, screen_coords[0], screen_coords[1], screen_coords[2], color);
            }
        }
    }


    // Заливка треугольников модели с учетом нормалей и направления света
    // и с использованием z-буфера для отсечения ненужных пикселей
    // light_dir - вектор направление света
    void fill_model_with_z_buffer(Model *model, Image &image, Vec3f &light_dir)
    {
        int width = image.width();
        int height = image.height();
        const int depth  = 255;

        // Поскольку у нас экран двумерный, то z-буфер тоже должен быть двумерным:
        auto size = width*height;
        if (_zbuffer.size() != size)
            _zbuffer.resize(size);

        for (int i=0; i<width*height; i++) {
            _zbuffer[i] = std::numeric_limits<int>::min();
        }

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            Vec3i screen_coords[3];
            Vec3f world_coords[3];
            for (int j=0; j<3; j++) {
                Vec3f v = model->vert(face[j].idxVertex);
                screen_coords[j] = Vec3i((v.x+1.)*width/2., (v.y+1.)*height/2., (v.z+1.)*depth/2.);
                world_coords[j]  = v;
            }
//            Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);    // CA ^ BA
            Vec3f n = (world_coords[0]-world_coords[1])^(world_coords[0]-world_coords[2]);    // AB ^ AC
//            Vec3f n = (world_coords[0]-world_coords[2])^(world_coords[0]-world_coords[1]);      // AC ^ AB
            n.normalize();
            float intensity = n*light_dir;
            if (intensity>0) {
                Pixel color = {intensity*255, intensity*255, intensity*255, 255};
                _painter.fill_triangle(image, screen_coords[0], screen_coords[1], screen_coords[2], color, _zbuffer);
            }
        }
    }

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
    double CalcIntensity(Vec3f n, Vec3f light_dir)
    {
//            Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
        n.normalize();
        double intensity = n*light_dir;
        return intensity;
    }

    // Заливка треугольника методом Гуро
    // Аналог fill_triangle - с использованием z-буфера для отсечения ненужных пикселей
    void fill_triangle_guro(triangleVertex t[3], Image &image, Vec3f &light_dir, std::vector<int> &zbuffer)
    {
        auto &tr0 = t[0];
        auto &tr1 = t[1];
        auto &tr2 = t[2];

        Vec3i &t0 = t[0].screen_v;
        Vec3i &t1 = t[1].screen_v;
        Vec3i &t2 = t[2].screen_v;

        int width = image.width();
        int height = image.height();
        double intensity = 0;

        light_dir = light_dir*-1;

        // ToDo расчет нормалей для теста (убрать потом)
//        Vec3f n = (t[2].world_v-t[0].world_v)^(t[1].world_v-t[0].world_v);
        Vec3f n = (t[1].world_v-t[0].world_v)^(t[2].world_v-t[0].world_v);
        n.normalize();
        float intensityToDo = n*light_dir;

        t[0].n.normalize();
        t[1].n.normalize();
        t[2].n.normalize();

        if (t0.y==t1.y && t0.y==t2.y) return; // i dont care about degenerate triangles
        if (t0.y>t1.y) std::swap(t0, t1);
        if (t0.y>t2.y) std::swap(t0, t2);
        if (t1.y>t2.y) std::swap(t1, t2);
        int total_height = t2.y-t0.y;
        for (int i=0; i<total_height; i++) {
            bool second_half = i>t1.y-t0.y || t1.y==t0.y;
            int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
            float alpha = (float)i/total_height;
            float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
            Vec3i A =               t0 + Vec3f(t2-t0)*alpha;
            Vec3i B = second_half ? t1 + Vec3f(t2-t1)*beta : t0 + Vec3f(t1-t0)*beta;
            if (A.x>B.x) std::swap(A, B);

            // Интерполяция Гуро
            // Интенсивность в вершинах треугольника
            double intensT0 = t[0].n*light_dir;
            double intensT1 = t[1].n*light_dir;
            double intensT2 = t[2].n*light_dir;

            // koefA и koefB - коэффициент интенсивности точек A и B на ребрах треугольника
            double koefA = t0.x == t1.x ? 1. : (A.x - t1.x) / (t0.x - t1.x); // (1)
            double koefB = t0.x == t2.x ? 1. : (B.x - t2.x) / (t0.x - t2.x); // (2)

            // Интенсивность света точек A и B на ребрах треугольника
            double intensA = koefA * intensT0 + (1.0 - koefA) * intensT1;
            double intensB = koefB * intensT0 + (1.0 - koefB) * intensT2;

            for (int j=A.x; j<=B.x; j++) {
                float phi = B.x==A.x ? 1. : (float)(j-A.x)/(float)(B.x-A.x);
                Vec3i P = Vec3f(A) + Vec3f(B-A)*phi;
                int idx = P.x+P.y*width;
                if (idx < zbuffer.size() && zbuffer[idx]<P.z) {
                    zbuffer[idx] = P.z;

                    // Интенсивность закрашиваемого пикселся
                    double koef = B.x == A.x ? 1. : (B.x - P.x) / (B.x - A.x);
                    intensity = koef * intensA + (1.0 - koef) * intensB;    // (3)

//                    // приращение интенсивности
//                    double deltaIdeltaT = (intensA - intensB) * (koefA - koefB);// (4)
//                    intensity += deltaIdeltaT;

                    intensity = intensityToDo;
//                    intensity = (intensT0+intensT1+intensT2)/3;

                    if(intensity > 0)
                    {
                        Pixel color = {intensity * 255, intensity * 255, intensity * 255, 255};
                        image.set(P.x, P.y, color);
                    }
                }
            }
        }
    }

    // Заливка треугольника методом Гуро
    // Аналог fill_triangle - с использованием z-буфера для отсечения ненужных пикселей
    // TODO неееееее раааботаает :)
    void fill_triangle_guro2(triangleVertex t[3], Image &image, Vec3f &light_dir, std::vector<int> &zbuffer)
    {
        Vec3i &t0 = t[0].screen_v;
        Vec3i &t1 = t[1].screen_v;
        Vec3i &t2 = t[2].screen_v;

        // ToDo расчет нормалей для теста (убрать потом)
        Vec3f n = (t[2].world_v -t[0].world_v)^(t[1].world_v-t[0].world_v);
        n.normalize();
        double intensityToDo = n*light_dir;

        int width = image.width();
        int height = image.height();

        if (t0.y==t1.y && t0.y==t2.y) return; // i dont care about degenerate triangles
        if (t0.y>t1.y) std::swap(t0, t1);
        if (t0.y>t2.y) std::swap(t0, t2);
        if (t1.y>t2.y) std::swap(t1, t2);
        int total_height = t2.y-t0.y;
        for (int i=0; i<total_height; i++)
        {
            bool second_half = i>t1.y-t0.y || t1.y==t0.y;
            int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
            float alpha = (float)i/total_height;
            float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
            Vec3i A =               t0 + Vec3f(t2-t0)*alpha;
            Vec3i B = second_half ? t1 + Vec3f(t2-t1)*beta : t0 + Vec3f(t1-t0)*beta;
            if (A.x>B.x) std::swap(A, B);

            // Интерполяция Гуро
            // Интенсивность в вершинах треугольника
            double intensT0 = CalcIntensity(t[0].n, light_dir);
            double intensT1 = CalcIntensity(t[1].n, light_dir);
            double intensT2 = CalcIntensity(t[2].n, light_dir);

            // koefA и koefB - коэффициент интенсивности точек A и B на ребрах треугольника
            double koefA = t0.x == t1.x ? 1. : (A.x - t1.x) / (t0.x - t1.x); // (1)
            double koefB = t0.x == t2.x ? 1. : (B.x - t2.x) / (t0.x - t2.x); // (2)

            // Интенсивность света точек A и B на ребрах треугольника
            double intensA = koefA * intensT0 + (1.0 - koefA) * intensT1;
            double intensB = koefB * intensT0 + (1.0 - koefB) * intensT2;

            for (int j=A.x; j<=B.x; j++)
            {
                float phi = B.x==A.x ? 1. : (float)(j-A.x)/(float)(B.x-A.x);
                Vec3i P = Vec3f(A) + Vec3f(B-A)*phi;
                int idx = P.x+P.y*width;
                if (idx < zbuffer.size() && zbuffer[idx]<P.z) {
                    zbuffer[idx] = P.z;

                    // Интенсивность закрашиваемого пикселся
                    double koef = B.x == A.x ? 1. : (B.x - P.x) / (B.x - A.x);
                    double intens = koef * intensA + (1.0 - koef) * intensB;    // (3)

//                    // приращение интенсивности
//                    double deltaIdeltaT = (intensA - intensB) * (koefA - koefB);// (4)
//                    intens += deltaIdeltaT;

//                    double intens = intensityToDo;
                    Pixel color = {intens*255, intens*255, intens*255, 255};
                    image.set(P.x, P.y, color);
                }
            }
        }
    }

    // Аналог fill_model_with_z_buffer
    // Заливка методом Гуро
    void fill_model_with_z_buffer2(Model *model, Image &image, Vec3f &light_dir)
    {
        int width = image.width();
        int height = image.height();
        const int depth  = 255;

        // Поскольку у нас экран двумерный, то z-буфер тоже должен быть двумерным:
        auto size = width*height;
        if (_zbuffer.size() != size)
            _zbuffer.resize(size);

        for (int i=0; i<width*height; i++) {
            _zbuffer[i] = std::numeric_limits<int>::min();
        }

        for (int i=0; i<model->nfaces(); i++) {
            std::vector<faceVertex> face = model->face(i);
            Vec3i screen_coords[3];
            Vec3f world_coords[3];
            for (int j=0; j<3; j++) {
                Vec3f v = model->vert(face[j].idxVertex);
                screen_coords[j] = Vec3i((v.x+1.)*width/2., (v.y+1.)*height/2., (v.z+1.)*depth/2.);
                world_coords[j]  = v;
            }
//            Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
//            n.normalize();
//            double intensity = n*light_dir;

            triangleVertex t[3];
            t[0].screen_v = screen_coords[0];
            t[1].screen_v = screen_coords[1];
            t[2].screen_v = screen_coords[2];

            t[0].world_v = world_coords[0];
            t[1].world_v = world_coords[1];
            t[2].world_v = world_coords[2];

            t[0].n = model->normal(face[0].idxNormal);
            t[1].n = model->normal(face[1].idxNormal);
            t[2].n = model->normal(face[2].idxNormal);

//            fill_triangle_guro(t, image, light_dir, _zbuffer);
            fill_triangle_guro2(t, image, light_dir, _zbuffer);
        }
    }
};


#endif //QTGUIEXAMPLE_MYPAINTER_H
