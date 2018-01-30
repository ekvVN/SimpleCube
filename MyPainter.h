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


class MyPainter
{
public:
    /*
     * Нарисовать что-то)
     * arr - указатель на массив пикселей
     * width - ширина изображения
     * height - выоста изображения
     */
    void DrawCube(Pixel *pixs, int width, int height);
};


#endif //QTGUIEXAMPLE_MYPAINTER_H
