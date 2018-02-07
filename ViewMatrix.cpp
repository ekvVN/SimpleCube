//
// Created by root on 07.02.18.
//

#include "ViewMatrix.h"

ViewMatrix::ViewMatrix()
    : width(1)
    , height(1)
    , eye(0, 0, 3)
    , center(0, 0, 0)
    , up(0, 1, 0)
{
}

Matrix ViewMatrix::operator*(const Matrix &a)
{
    return _m * a;
}

void ViewMatrix::calcViewMatrix()
{
    auto modelView = Matrix::lookat(eye, center, up);
    auto projection = Matrix::identity(4);
//    auto viewPort = Matrix::viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4);
    auto viewPort = Matrix::viewport(0, 0, width, height);
//    projection[3][2] = -1.f / (eye - center).norm();

    _m = (viewPort * projection * modelView);
}
