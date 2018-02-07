//
// Created by root on 07.02.18.
//

#ifndef QTGUIEXAMPLE_VIEWMATRIX_H
#define QTGUIEXAMPLE_VIEWMATRIX_H

#include "geometry.h"

// класс матрицы вида с камеры
class ViewMatrix
{
public:
    int width;    // ширина вьюпорта
    int height;   // высота вьюпорта
    Vec3f eye;    // вектор - куда смотрим
    Vec3f center; // координаты центра сцены
    Vec3f up;     // направление вверх

public:
    ViewMatrix();

    Matrix operator*(const Matrix& a);
    void calcViewMatrix();

private:
    Matrix _m;     // расчитанная матрица
};


#endif //QTGUIEXAMPLE_VIEWMATRIX_H
