//
// Created by root on 31.01.18.
//

#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <iostream>

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

const Matrix3x3<char> zero_matrix_c( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
const Matrix3x3<short> zero_matrix_s( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
const Matrix3x3<int> zero_matrix( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
const Matrix3x3<long> zero_matrix_l( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
const Matrix3x3<long long> zero_matrix_ll( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
const Matrix3x3<float> zero_matrix_f( 0, 0, 0, 0, 0, 0, 0, 0, 0 );
const Matrix3x3<double> zero_matrix_d( 0, 0, 0, 0, 0, 0, 0, 0, 0 );

const Matrix3x3<char> unit_matrix_c( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
const Matrix3x3<short> unit_matrix_s( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
const Matrix3x3<int> unit_matrix( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
const Matrix3x3<long> unit_matrix_l( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
const Matrix3x3<long long> unit_matrix_ll( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
const Matrix3x3<float> unit_matrix_f( 1, 0, 0, 0, 1, 0, 0, 0, 1 );
const Matrix3x3<double> unit_matrix_d( 1, 0, 0, 0, 1, 0, 0, 0, 1 );

#endif //MATRIX3X3_H
