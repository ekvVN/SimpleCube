//
// Created by ekvvn on 06.02.18.
//

#ifndef QTGUIEXAMPLE_IMAGE_H
#define QTGUIEXAMPLE_IMAGE_H

#include "geometry.h"

struct Pixel
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
    unsigned char A;

    Pixel operator *(float intensity)
    {
        Pixel res = *this;
        intensity = intensity > 1.f
            ? 1.f
            : (intensity < 0.f ? 0.f :intensity);

        res.B = static_cast<unsigned char>(B*intensity);
        res.G = static_cast<unsigned char>(G*intensity);
        res.R = static_cast<unsigned char>(R*intensity);
        return res;
    }
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

    int width()
    { return _width; }

    int height()
    { return _height; }

private:
    Pixel *_pixs;
    int _width;
    int _height;
};

#endif //QTGUIEXAMPLE_IMAGE_H
