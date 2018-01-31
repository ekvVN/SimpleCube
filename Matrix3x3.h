//
// Created by root on 31.01.18.
//

#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <iostream>
#include "geometry.h"
#include <math.h>

template<typename T>
class Matrix3x3
{
    public:
    T _m11, _m12, _m13;
    T _m21, _m22, _m23;
    T _m31, _m32, _m33;

    Matrix3x3()
    { };

    Matrix3x3(T m11, T m12, T m13,
           T m21, T m22, T m23,
           T m31, T m32, T m33)
        : _m11(m11), _m12(m12), _m13(m13),
          _m21(m21), _m22(m22), _m23(m23),
          _m31(m31), _m32(m32), _m33(m33)
    { };

    Matrix3x3(const Matrix3x3& m)
        : _m11(m._m11), _m12(m._m12), _m13(m._m13),
          _m21(m._m21), _m22(m._m22), _m23(m._m23),
          _m31(m._m31), _m32(m._m32), _m33(m._m33)
    { };

    ~Matrix3x3()
    { };

    Matrix3x3& operator=(const Matrix3x3& rhs)
    {
        _m11 = rhs._m11; _m12 = rhs._m12; _m13 = rhs._m13;
        _m21 = rhs._m21; _m22 = rhs._m22; _m23 = rhs._m23;
        _m31 = rhs._m31; _m32 = rhs._m32; _m33 = rhs._m33;
        return *this;
    };

    bool operator==(const Matrix3x3& rhs) const
    {
        return _m11 == rhs._m11 && _m12 == rhs._m12 && _m13 == rhs._m13
            && _m21 == rhs._m21 && _m22 == rhs._m22 && _m23 == rhs._m23
            && _m31 == rhs._m31 && _m32 == rhs._m32 && _m33 == rhs._m33;
    };

    Matrix3x3 operator+(const Matrix3x3& rhs) const
    {
        Matrix3x3 out_matrix(
            _m11 + rhs._m11, _m12 + rhs._m12, _m13 + rhs._m13,
            _m21 + rhs._m21, _m22 + rhs._m22, _m23 + rhs._m23,
            _m31 + rhs._m31, _m32 + rhs._m32, _m33 + rhs._m33);
        return out_matrix;
    };

    Matrix3x3 operator+=(const Matrix3x3& rhs) const
    {
        _m11 += rhs._m11; _m12 += rhs._m12; _m13 += rhs._m13;
        _m21 += rhs._m21; _m22 += rhs._m22; _m23 += rhs._m23;
        _m31 += rhs._m31; _m32 += rhs._m32; _m33 += rhs._m33;
        return *this;
    };


    Matrix3x3 operator-(const Matrix3x3& rhs) const
    {
        Matrix3x3 out_matrix(
            _m11 - rhs._m11, _m12 - rhs._m12, _m13 - rhs._m13,
            _m21 - rhs._m21, _m22 - rhs._m22, _m23 - rhs._m23,
            _m31 - rhs._m31, _m32 - rhs._m32, _m33 - rhs._m33);
        return out_matrix;
    };

    Matrix3x3 operator-=(const Matrix3x3& rhs) const
    {
        _m11 -= rhs._m11; _m12 -= rhs._m12; _m13 -= rhs._m13;
        _m21 -= rhs._m21; _m22 -= rhs._m22; _m23 -= rhs._m23;
        _m31 -= rhs._m31; _m32 -= rhs._m32; _m33 -= rhs._m33;
        return *this;
    };

    Matrix3x3 operator*(const Matrix3x3& rhs) const
    {
        Matrix3x3 out_matrix;
        out_matrix._m11 = _m11 * rhs._m11 + _m12 * rhs._m21 + _m13 * rhs._m31;
        out_matrix._m12 = _m11 * rhs._m12 + _m12 * rhs._m22 + _m13 * rhs._m32;
        out_matrix._m13 = _m11 * rhs._m13 + _m12 * rhs._m23 + _m13 * rhs._m33;
        out_matrix._m21 = _m21 * rhs._m11 + _m22 * rhs._m21 + _m23 * rhs._m31;
        out_matrix._m22 = _m21 * rhs._m12 + _m22 * rhs._m22 + _m23 * rhs._m32;
        out_matrix._m23 = _m21 * rhs._m13 + _m22 * rhs._m23 + _m23 * rhs._m33;
        out_matrix._m31 = _m31 * rhs._m11 + _m32 * rhs._m21 + _m33 * rhs._m31;
        out_matrix._m32 = _m31 * rhs._m12 + _m32 * rhs._m22 + _m33 * rhs._m32;
        out_matrix._m33 = _m31 * rhs._m13 + _m32 * rhs._m23 + _m33 * rhs._m33;
        return out_matrix;
    };

    Matrix3x3 operator*(const T& val) const
    {
        Matrix3x3 out_matrix(
            _m11 * val, _m12 * val, _m13 * val,
            _m21 * val, _m22 * val, _m23 * val,
            _m31 * val, _m32 * val, _m33 * val);
        return out_matrix;
    };

    Matrix3x3 operator*=(const T& rhs) const
    {
        _m11 *= rhs._m11; _m12 *= rhs._m12; _m13 *= rhs._m13;
        _m21 *= rhs._m21; _m22 *= rhs._m22; _m23 *= rhs._m23;
        _m31 *= rhs._m31; _m32 *= rhs._m32; _m33 *= rhs._m33;
        return *this;
    };

    Matrix3x3 operator/(const T& val) const
    {
        Matrix3x3 out_matrix(
            _m11 / val, _m12 / val, _m13 / val,
            _m21 / val, _m22 / val, _m23 / val,
            _m31 / val, _m32 / val, _m33 / val);
        return out_matrix;
    };

    Matrix3x3 operator/=(const T& rhs) const
    {
        _m11 /= rhs._m11; _m12 /= rhs._m12; _m13 /= rhs._m13;
        _m21 /= rhs._m21; _m22 /= rhs._m22; _m23 /= rhs._m23;
        _m31 /= rhs._m31; _m32 /= rhs._m32; _m33 /= rhs._m33;
        return *this;
    };
};

template<typename T>
Matrix3x3<T> operator*(const T& val, const Matrix3x3<T>& m)
{
    Matrix3x3<T> res(m);
    res._m11 *= val; res._m12 *= val; res._m13 *= val;
    res._m21 *= val; res._m22 *= val; res._m23 *= val;
    res._m31 *= val; res._m32 *= val; res._m33 *= val;
    return res;
};

template<typename T>
T determinant(const Matrix3x3<T>& m)
{
    return    m._m11 * (m._m22 * m._m33 - m._m23 * m._m32)
            - m._m12 * (m._m21 * m._m33 - m._m23 * m._m31)
            + m._m13 * (m._m21 * m._m32 - m._m22 * m._m31);
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Matrix3x3<T>& m)
{
    stream << "["
           << m._m11 << " " << m._m12 << " " << m._m13 << ", "
           << m._m21 << " " << m._m22 << " " << m._m23 << ", "
           << m._m31 << " " << m._m32 << " " << m._m33 << "]";
    return stream;
};

template<typename T>
std::wostream& operator<<(std::wostream& stream, const Matrix3x3<T>& m)
{
    stream << L"["
           << m._m11 << L" " << m._m12 << L" " << m._m13 << L", "
           << m._m21 << L" " << m._m22 << L" " << m._m23 << L", "
           << m._m31 << L" " << m._m32 << L" " << m._m33 << L"]";
    return stream;
};

// Получить матрицу поворота относительно произвольной оси на заданный угол (в радианах)
// vec - ось
// radAngle - угол в радианах
template<class T>
Matrix3x3<T> GetRotateMatrix(Vec3<T> vec, T radAngle)
{
    T x = vec.x;
    T y = vec.y;
    T z = vec.z;
    T sinA = sin(radAngle);
    T cosA = cos(radAngle);

    T m11 = cosA + (1.0 - cosA) * x * x;
    T m12 = (1.0 - cosA) * x * y - sinA * z;
    T m13 = (1.0 - cosA) * x * z + sinA * y;

    T m21 = (1.0 - cosA) * y * x + sinA * z;
    T m22 = cosA + (1.0 - cosA) * y * y;
    T m23 = (1.0 - cosA) * y * z - sinA * x;

    T m31 = (1.0 - cosA) * z * x - sinA * y;
    T m32 = (1.0 - cosA) * z * y + sinA * x;
    T m33 = cosA + (1.0 - cosA) * z * z;

    Matrix3x3<T> rotateMatrix(
        m11, m12, m13,
        m21, m22, m23,
        m31, m32, m33
    );
    return rotateMatrix;
}

template<typename T>
Vec3<T> operator*(Vec3<T> v, Matrix3x3<T>& m)
{
    Vec3<T> res;
    res.x = v.x * m._m11 + v.y * m._m21 + v.z * m._m31;
    res.y = v.x * m._m12 + v.y * m._m22 + v.z * m._m32;
    res.z = v.x * m._m13 + v.y * m._m23 + v.z * m._m33;
    return res;
};
#endif //MATRIX3X3_H
