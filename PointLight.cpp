//
// Created by root on 12.02.18.
//

#include "PointLight.h"
#include "geometry.h"

PointLight::PointLight()
    : _lightPos(Vec3f(0, 0, 1))
    , _lightDir(Vec3f(0, 0, 1))
    , _lightIntens(1.0f)
    , _kd(1.0f)
{
}

float PointLight::operator*(const Vec3f &n)
{
    // скалярное произведение вектора нормали на вектор света ===> косинус угла между ними
    auto cosA = n * _lightDir;
    return _lightIntens * _kd * cosA;
}

Vec3f PointLight::lightPosition()
{
    return _lightPos;
}

void PointLight::setLightPosition(Vec3f lightPos)
{
    _lightPos = lightPos;
}

void PointLight::setLightDir(Vec3f lightDir)
{
    _lightDir = lightDir.normalize();
}

void PointLight::setLightIntensity(float lightIntens)
{
    _lightIntens = lightIntens;
}

void PointLight::setKd(float kd)
{
    _kd = kd;
}
