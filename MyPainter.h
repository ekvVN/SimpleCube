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

    unsigned char A;
    unsigned char R;
    unsigned char G;
    unsigned char B;
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
     * arr - указатель на массив пикселей
     * width - ширина изображения
     * height - выоста изображения
     */
    void DrawCube(Pixel *pixs, int width, int height)
    {
        Image image(pixs, width, height);

        Pixel white = {255,255,255,255};
        Pixel blue = {255,0,0,255};

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
            line(13, 20, 80, 40, image, white);
            line(20, 13, 40, 80, image, blue);
            line(80, 40, 13, 20, image, blue);
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
};


#endif //QTGUIEXAMPLE_MYPAINTER_H
