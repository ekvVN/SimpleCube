//
// Created by root on 31.01.18.
//

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <iostream>
#include "geometry.h"
#include <math.h>

template<typename T>
class Matrix4x4
{
public:
    T _m11, _m12, _m13, _m14;
    T _m21, _m22, _m23, _m24;
    T _m31, _m32, _m33, _m34;
    T _m41, _m42, _m43, _m44;

    Matrix4x4()
    { };

    Matrix4x4(T m11, T m12, T m13, T m14,
              T m21, T m22, T m23, T m24,
              T m31, T m32, T m33, T m34,
              T m41, T m42, T m43, T m44)
            : _m11(m11), _m12(m12), _m13(m13), _m14(m14),
              _m21(m21), _m22(m22), _m23(m23), _m24(m24),
              _m31(m31), _m32(m32), _m33(m33), _m34(m34),
              _m41(m41), _m42(m42), _m43(m43), _m44(m44)
    { };

    Matrix4x4(const Matrix4x4& m)
            : _m11(m._m11), _m12(m._m12), _m13(m._m13), _m14(m._m14),
              _m21(m._m21), _m22(m._m22), _m23(m._m23), _m24(m._m24),
              _m31(m._m31), _m32(m._m32), _m33(m._m33), _m34(m._m34),
              _m41(m._m41), _m42(m._m42), _m43(m._m43), _m44(m._m44)
    { };

    ~Matrix4x4()
    { };

    Matrix4x4& operator=(const Matrix4x4& rhs)
    {
        _m11 = rhs._m11; _m12 = rhs._m12; _m13 = rhs._m13; _m14 = rhs._m14;
        _m21 = rhs._m21; _m22 = rhs._m22; _m23 = rhs._m23; _m24 = rhs._m24;
        _m31 = rhs._m31; _m32 = rhs._m32; _m33 = rhs._m33; _m34 = rhs._m34;
        _m41 = rhs._m41; _m42 = rhs._m42; _m43 = rhs._m43; _m44 = rhs._m44;
        return *this;
    };

    bool operator==(const Matrix4x4& rhs) const
    {
        return _m11 == rhs._m11 && _m12 == rhs._m12 && _m13 == rhs._m13 && _m14 == rhs._m14
            && _m21 == rhs._m21 && _m22 == rhs._m22 && _m23 == rhs._m23 && _m24 == rhs._m24
            && _m31 == rhs._m31 && _m32 == rhs._m32 && _m33 == rhs._m33 && _m34 == rhs._m34
            && _m41 == rhs._m41 && _m42 == rhs._m42 && _m43 == rhs._m43 && _m44 == rhs._m44;
    };

    Matrix4x4 operator+(const Matrix4x4& rhs) const
    {
        Matrix4x4 out_matrix(
                _m11 + rhs._m11, _m12 + rhs._m12, _m13 + rhs._m13, _m14 + rhs._m14,
                _m21 + rhs._m21, _m22 + rhs._m22, _m23 + rhs._m23, _m24 + rhs._m24,
                _m31 + rhs._m31, _m32 + rhs._m32, _m33 + rhs._m33, _m34 + rhs._m34,
                _m41 + rhs._m41, _m42 + rhs._m42, _m43 + rhs._m43, _m44 + rhs._m44);
        return out_matrix;
    };

    Matrix4x4 operator+=(const Matrix4x4& rhs) const
    {
        _m11 += rhs._m11; _m12 += rhs._m12; _m13 += rhs._m13; _m14 += rhs._m14;
        _m21 += rhs._m21; _m22 += rhs._m22; _m23 += rhs._m23; _m24 += rhs._m24;
        _m31 += rhs._m31; _m32 += rhs._m32; _m33 += rhs._m33; _m34 += rhs._m34;
        _m41 += rhs._m41; _m42 += rhs._m42; _m43 += rhs._m43; _m44 += rhs._m44;
        return *this;
    };

    Matrix4x4 operator-(const Matrix4x4& rhs) const
    {
        Matrix4x4 out_matrix(
                _m11 - rhs._m11, _m12 - rhs._m12, _m13 - rhs._m13, _m14 - rhs._m14,
                _m21 - rhs._m21, _m22 - rhs._m22, _m23 - rhs._m23, _m24 - rhs._m24,
                _m31 - rhs._m31, _m32 - rhs._m32, _m33 - rhs._m33, _m34 - rhs._m34,
                _m41 - rhs._m41, _m42 - rhs._m42, _m43 - rhs._m43, _m44 - rhs._m44);
        return out_matrix;
    };

    Matrix4x4 operator-=(const Matrix4x4& rhs) const
    {
        _m11 -= rhs._m11; _m12 -= rhs._m12; _m13 -= rhs._m13; _m14 -= rhs._m14;
        _m21 -= rhs._m21; _m22 -= rhs._m22; _m23 -= rhs._m23; _m24 -= rhs._m24;
        _m31 -= rhs._m31; _m32 -= rhs._m32; _m33 -= rhs._m33; _m34 -= rhs._m34;
        _m41 -= rhs._m41; _m42 -= rhs._m42; _m43 -= rhs._m43; _m44 -= rhs._m44;
        return *this;
    };

//    Matrix3x3 operator*(const Matrix3x3& rhs) const
//    {
//        Matrix3x3 out_matrix;
//        out_matrix._m11 = _m11 * rhs._m11 + _m12 * rhs._m21 + _m13 * rhs._m31;
//        out_matrix._m12 = _m11 * rhs._m12 + _m12 * rhs._m22 + _m13 * rhs._m32;
//        out_matrix._m13 = _m11 * rhs._m13 + _m12 * rhs._m23 + _m13 * rhs._m33;
//        out_matrix._m21 = _m21 * rhs._m11 + _m22 * rhs._m21 + _m23 * rhs._m31;
//        out_matrix._m22 = _m21 * rhs._m12 + _m22 * rhs._m22 + _m23 * rhs._m32;
//        out_matrix._m23 = _m21 * rhs._m13 + _m22 * rhs._m23 + _m23 * rhs._m33;
//        out_matrix._m31 = _m31 * rhs._m11 + _m32 * rhs._m21 + _m33 * rhs._m31;
//        out_matrix._m32 = _m31 * rhs._m12 + _m32 * rhs._m22 + _m33 * rhs._m32;
//        out_matrix._m33 = _m31 * rhs._m13 + _m32 * rhs._m23 + _m33 * rhs._m33;
//        return out_matrix;
//    };

    Matrix4x4 operator*(const T& val) const
    {
        Matrix4x4 out_matrix(
                _m11 * val, _m12 * val, _m13 * val, _m14 * val,
                _m21 * val, _m22 * val, _m23 * val, _m24 * val,
                _m31 * val, _m32 * val, _m33 * val, _m34 * val,
                _m41 * val, _m42 * val, _m43 * val, _m44 * val);
        return out_matrix;
    };

    Matrix4x4 operator*=(const T& rhs) const
    {
        _m11 *= rhs._m11; _m12 *= rhs._m12; _m13 *= rhs._m13; _m14 *= rhs._m14;
        _m21 *= rhs._m21; _m22 *= rhs._m22; _m23 *= rhs._m23; _m24 *= rhs._m24;
        _m31 *= rhs._m31; _m32 *= rhs._m32; _m33 *= rhs._m33; _m34 *= rhs._m34;
        _m41 *= rhs._m41; _m42 *= rhs._m42; _m43 *= rhs._m43; _m44 *= rhs._m44;
        return *this;
    };

    Matrix4x4 operator/(const T& val) const
    {
        Matrix4x4 out_matrix(
                _m11 / val, _m12 / val, _m13 / val, _m14 / val,
                _m21 / val, _m22 / val, _m23 / val, _m24 / val,
                _m31 / val, _m32 / val, _m33 / val, _m34 / val,
                _m41 / val, _m42 / val, _m43 / val, _m44 / val);
        return out_matrix;
    };

    Matrix4x4 operator/=(const T& rhs) const
    {
        _m11 /= rhs._m11; _m12 /= rhs._m12; _m13 /= rhs._m13; _m14 /= rhs._m14;
        _m21 /= rhs._m21; _m22 /= rhs._m22; _m23 /= rhs._m23; _m24 /= rhs._m24;
        _m31 /= rhs._m31; _m32 /= rhs._m32; _m33 /= rhs._m33; _m34 /= rhs._m34;
        return *this;
    };
};

template<typename T>
Matrix4x4<T> operator*(const T& val, const Matrix4x4<T>& m)
{
    Matrix4x4<T> res(m);
    res._m11 *= val; res._m12 *= val; res._m13 *= val; res._m14 *= val;
    res._m21 *= val; res._m22 *= val; res._m23 *= val; res._m24 *= val;
    res._m31 *= val; res._m32 *= val; res._m33 *= val; res._m34 *= val;
    res._m41 *= val; res._m42 *= val; res._m43 *= val; res._m44 *= val;
    return res;
};

//template<typename T>
//T determinant(const Matrix3x3<T>& m)
//{
//    return    m._m11 * (m._m22 * m._m33 - m._m23 * m._m32)
//            - m._m12 * (m._m21 * m._m33 - m._m23 * m._m31)
//            + m._m13 * (m._m21 * m._m32 - m._m22 * m._m31);
//};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Matrix4x4<T>& m)
{
    stream << "["
           << m._m11 << " " << m._m12 << " " << m._m13 << " " << m._m14 << ", "
           << m._m21 << " " << m._m22 << " " << m._m23 << " " << m._m24 << ", "
           << m._m31 << " " << m._m32 << " " << m._m33 << " " << m._m34 << ", "
           << m._m41 << " " << m._m42 << " " << m._m43 << " " << m._m44 << "]";
    return stream;
};

template<typename T>
std::wostream& operator<<(std::wostream& stream, const Matrix4x4<T>& m)
{
    stream << L"["
           << m._m11 << L" " << m._m12 << L" " << m._m13 << L" " << m._m14 << L", "
           << m._m21 << L" " << m._m22 << L" " << m._m23 << L" " << m._m24 << L", "
           << m._m31 << L" " << m._m32 << L" " << m._m33 << L" " << m._m34 << L", "
           << m._m41 << L" " << m._m42 << L" " << m._m43 << L" " << m._m44 << L"]";
    return stream;
};

//const Matrix3x3<char> zero_matrix_c( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
//const Matrix3x3<short> zero_matrix_s( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
//const Matrix3x3<int> zero_matrix( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
//const Matrix3x3<long> zero_matrix_l( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
//const Matrix3x3<long long> zero_matrix_ll( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
//const Matrix3x3<float> zero_matrix_f( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
//const Matrix3x3<double> zero_matrix_d( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
//
//const Matrix3x3<char> unit_matrix_c( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
//const Matrix3x3<short> unit_matrix_s( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
//const Matrix3x3<int> unit_matrix( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
//const Matrix3x3<long> unit_matrix_l( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
//const Matrix3x3<long long> unit_matrix_ll( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
//const Matrix3x3<float> unit_matrix_f( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
//const Matrix3x3<double> unit_matrix_d( 1, 0, 0, 0, 1, 0, 0, 0, 1 );

// Получить матрицу поворота относительно произвольной оси на заданный угол (в радианах)
// vec - ось
// radAngle - угол в радианах
template<class T>
Matrix4x4<T> GetRotateMatrix(Vec3<T> vec, T radAngle)
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

    Matrix4x4<T> rotateMatrix(
        m11, m12, m13, 0.0,
        m21, m22, m23, 0.0,
        m31, m32, m33, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    return rotateMatrix;
}

template<typename T>
Vec3<T> operator*(Vec3<T> v, Matrix4x4<T>& m)
{
    Vec3<T> res;
    res.x = v.x * m._m11 + v.y * m._m21 + v.z * m._m31;
    res.y = v.x * m._m12 + v.y * m._m22 + v.z * m._m32;
    res.z = v.x * m._m13 + v.y * m._m23 + v.z * m._m33;
    return res;
};

#endif //MATRIX4X4_H
