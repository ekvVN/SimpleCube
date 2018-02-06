//
// Created by ekvvn on 06.02.18.
//

#ifndef QTGUIEXAMPLE_IMAGE_H
#define QTGUIEXAMPLE_IMAGE_H

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
