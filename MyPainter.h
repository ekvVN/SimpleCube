//
// Created by root on 30.01.18.
//

#ifndef QTGUIEXAMPLE_MYPAINTER_H
#define QTGUIEXAMPLE_MYPAINTER_H

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
public:
    /*
     * Нарисовать что-то :)
     * arr - указатель на массив пикселей
     * width - ширина изображения
     * height - выоста изображения
     */
    void DrawCube(Pixel *pixs, int width, int height)
    {
        Image image(pixs, width, height);

        line(13, 20, 80, 40, image, {255,255,255,255});
        line(20, 13, 40, 80, image, {255,0,0,255});
        line(80, 40, 13, 20, image, {255,0,0,255});
    }

    void line(int x0, int y0, int x1, int y1, Image &image, Pixel color) {
        for (int x=x0; x<=x1; x++) {
            float t = (x-x0)/(float)(x1-x0);
            int y = y0*(1.-t) + y1*t;
            image.set(x, y, color);
        }
    }
};


#endif //QTGUIEXAMPLE_MYPAINTER_H
