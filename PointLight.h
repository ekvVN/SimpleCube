//
// Created by root on 12.02.18.
//

#ifndef QTGUIEXAMPLE_POINTLIGHT_H
#define QTGUIEXAMPLE_POINTLIGHT_H


#include "geometry.h"

class PointLight
{
public:
    PointLight();

    // Посчитать интенсивность для нормали
    float operator*(const Vec3f &n);

    // Положение источника света
    Vec3f lightPosition();
    void setLightPosition(Vec3f lightPos);

    // Направление света
    void setLightDir(Vec3f lightDir);

    // Интенсивность источника света
    void setLightIntensity(float lightIntens);

    // Коэффициент Kd
    void setKd(float kd);

private:
    Vec3f _lightPos;
    Vec3f _lightDir;
    float _lightIntens;
    float _kd;
};


#endif //QTGUIEXAMPLE_POINTLIGHT_H
