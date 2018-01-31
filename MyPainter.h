//
// Created by root on 30.01.18.
//

#ifndef QTGUIEXAMPLE_MYPAINTER_H
#define QTGUIEXAMPLE_MYPAINTER_H

#include <cmath>
#include <utility>

#include "model.h"

struct Pixel
{

    unsigned char B;
    unsigned char G;
    unsigned char R;
    unsigned char A;
};

class Image
{
public:
    Image(Pixel *pixs, int width, int height)
        : _pixs(pixs)
        , _width(width)
        , _height(height)
    {}

    bool set(int x, int y, Pixel pix)
    {
        if (!_pixs || x<0 || y<0 || x>=_width || y>=_height) {
            return false;
        }

        _pixs[x+y*_width] = pix;
        return true;
    }

private:
    Pixel *_pixs;
    int _width;
    int _height;
};

class MyPainter
{
    Model *_model;
public:

    MyPainter()
        : _model(nullptr)
    {
    }

    void SetModel(Model *model)
    {
        _model = model;
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
            for (int i=0; i<_model->nfaces(); i++) {
                std::vector<int> face = _model->face(i);
                for (int j=0; j<3; j++) {
                    Vec3f v0 = _model->vert(face[j]);
                    Vec3f v1 = _model->vert(face[(j+1)%3]);
                    int x0 = (v0.x+1.)*width/2.;
                    int y0 = (v0.y+1.)*height/2.;
                    int x1 = (v1.x+1.)*width/2.;
                    int y1 = (v1.y+1.)*height/2.;
                    line(x0, y0, x1, y1, image, white);
                }
            }
        }
        else
        {
            // 1.1
            // line(13, 20, 80, 40, image, white);
            // line(20, 13, 40, 80, image, blue);
            // line(80, 40, 13, 20, image, blue);

            // 1.2
            line(Vec2i(13, 20), Vec2i(80, 40), image, white);
            line(Vec2i(20, 13), Vec2i(40, 80), image, blue);
            line(Vec2i(80, 40), Vec2i(13, 20), image, blue);

            // 2.
            Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
            Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
            Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

            triangle(t0[0], t0[1], t0[2], image, red);
            triangle(t1[0], t1[1], t1[2], image, green);
            triangle(t2[0], t2[1], t2[2], image, blue);

            Vec2i fill_t0[3] = {Vec2i(210, 70),   Vec2i(250, 160),  Vec2i(270, 80)};
            Vec2i fill_t1[3] = {Vec2i(380, 50),  Vec2i(350, 1),   Vec2i(270, 180)};
            Vec2i fill_t2[3] = {Vec2i(380, 150), Vec2i(320, 160), Vec2i(330, 180)};

            fill_triangle(fill_t0[0], fill_t0[1], fill_t0[2], image, red);
            fill_triangle(fill_t1[0], fill_t1[1], fill_t1[2], image, green);
            fill_triangle(fill_t2[0], fill_t2[1], fill_t2[2], image, blue);
        }
    }

    void line(int x0, int y0, int x1, int y1, Image &image, Pixel color) {
        bool steep = false;
        if (std::abs(x0-x1)<std::abs(y0-y1)) {
            std::swap(x0, y0);
            std::swap(x1, y1);
            steep = true;
        }
        if (x0>x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        int dx = x1-x0;
        int dy = y1-y0;
        int derror2 = std::abs(dy)*2;
        int error2 = 0;
        int y = y0;
        for (int x=x0; x<=x1; x++) {
            if (steep) {
                image.set(y, x, color);
            } else {
                image.set(x, y, color);
            }
            error2 += derror2;

            if (error2 > dx) {
                y += (y1>y0?1:-1);
                error2 -= dx*2;
            }
        }
    }

    void line(Vec2i p0, Vec2i p1, Image &image, Pixel color){
        line(p0.x, p0.y, p1.x, p1.y, image, color);
    }

    // Отрисовка контура треугольника
    void triangle(Vec2i t0, Vec2i t1, Vec2i t2, Image &image, Pixel color) {
        // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
        if (t0.y>t1.y) std::swap(t0, t1);
        if (t0.y>t2.y) std::swap(t0, t2);
        if (t1.y>t2.y) std::swap(t1, t2);

        line(t0, t1, image, color);
        line(t1, t2, image, color);
        line(t2, t0, image, color);
    }

    // Отрисовка закрашенного треугольника
    void fill_triangle(Vec2i t0, Vec2i t1, Vec2i t2, Image &image, Pixel color) {
        if (t0.y==t1.y && t0.y==t2.y) return; // i dont care about degenerate triangles
        // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
        if (t0.y>t1.y) std::swap(t0, t1);
        if (t0.y>t2.y) std::swap(t0, t2);
        if (t1.y>t2.y) std::swap(t1, t2);
        int total_height = t2.y-t0.y;
        for (int i=0; i<total_height; i++) {
            bool second_half = i>t1.y-t0.y || t1.y==t0.y;
            int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
            float alpha = (float)i/total_height;
            float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
            Vec2i A =               t0 + (t2-t0)*alpha;
            Vec2i B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
            if (A.x>B.x) std::swap(A, B);
            for (int j=A.x; j<=B.x; j++) {
                image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y
            }
        }
    }
};


#endif //QTGUIEXAMPLE_MYPAINTER_H
