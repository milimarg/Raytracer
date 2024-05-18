/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Color.hpp.cpp
*/

#include "Color.hpp"
#include "Interval.hpp"
#include "Math/Matrix/Matrix.hpp"

namespace rtx
{
    Color::Color()
        : _e{0, 0, 0, 1}
    {}

    Color::Color(double e0, double e1, double e2)
        : _e{e0, e1, e2, 1}
    {}

    Color::~Color()
    {}

    double Color::r() const
    {
        return _e[0];
    }

    double Color::g() const
    {
        return _e[1];
    }

    double Color::b() const
    {
        return _e[2];
    }

    double Color::a() const
    {
        return _e[3];
    }

    Color Color::operator-() const
    {
        return Color(-_e[0], -_e[1], -_e[2]);
    }

    double Color::operator[](int i) const
    {
        return _e[i];
    }

    double &Color::operator[](int i)
    {
        return _e[i];
    }

    Color &Color::operator+=(const Color &v)
    {
        _e[0] += v._e[0];
        _e[1] += v._e[1];
        _e[2] += v._e[2];
        return *this;
    }

    Color &Color::operator*=(double t)
    {
        _e[0] *= t;
        _e[1] *= t;
        _e[2] *= t;
        return *this;
    }

    Color &Color::operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double Color::length() const
    {
        return sqrt(lengthSquared());
    }

    double Color::lengthSquared() const
    {
        return _e[0] * _e[0] + _e[1] * _e[1] + _e[2] * _e[2];
    }

    bool Color::nearZero() const
    {
        auto s = 1e-8;
        return (std::fabs(_e[0]) < s) && (std::fabs(_e[1]) < s) && (std::fabs(_e[2]) < s);
    }

    Color Color::random()
    {
        return Color(Math::randomDouble(), Math::randomDouble(), Math::randomDouble());
    }

    Color Color::random(double min, double max)
    {
        return Color(Math::randomDouble(min,max), Math::randomDouble(min,max), Math::randomDouble(min,max));
    }

    std::ostream &operator<<(std::ostream &out, const Color &v)
    {
        return out << v._e[0] << ' ' << v._e[1] << ' ' << v._e[2];
    }

    Color operator+(const Color &u, const Color &v)
    {
        return Color(u._e[0] + v._e[0], u._e[1] + v._e[1], u._e[2] + v._e[2]);
    }

    Color operator+(const Color &u, const Vec3 &v)
    {
        return Color(u._e[0] + v._e[0], u._e[1] + v._e[1], u._e[2] + v._e[2]);
    }

    Color operator-(const Color &u, const Color &v)
    {
        return Color(u._e[0] - v._e[0], u._e[1] - v._e[1], u._e[2] - v._e[2]);
    }

    Color operator-(const Color &u, const Vec3 &v)
    {
        return Color(u._e[0] - v._e[0], u._e[1] - v._e[1], u._e[2] - v._e[2]);
    }

    Color operator*(const Color &u, const Color &v)
    {
        return Color(u._e[0] * v._e[0], u._e[1] * v._e[1], u._e[2] * v._e[2]);
    }

    Color operator*(const Color &u, const Vec3 &v)
    {
        return Color(u._e[0] * v._e[0], u._e[1] * v._e[1], u._e[2] * v._e[2]);
    }

    Color operator*(double t, const Color &v)
    {
        return Color(t*v._e[0], t*v._e[1], t*v._e[2]);
    }

    Color operator*(const Color &v, double t)
    {
        return t * v;
    }

    Color operator*(const Color &v, const Matrix &m)
    {
        Color result;

        result[0] = v.r() * m._data[0][0] + v.g() * m._data[1][0] + v.b() * m._data[2][0] + v.a() * m._data[3][0];
        result[1] = v.r() * m._data[0][1] + v.g() * m._data[1][1] + v.b() * m._data[2][1] + v.a() * m._data[3][1];
        result[2] = v.r() * m._data[0][2] + v.g() * m._data[1][2] + v.b() * m._data[2][2] + v.a() * m._data[3][2];
        result[3] = v.r() * m._data[0][0] + v.g() * m._data[1][3] + v.b() * m._data[2][3] + v.a() * m._data[3][3];
        return result;
    }

    Color operator/(const Color &v, double t)
    {
        return (1/t) * v;
    }

    double Color::linearToGamma(double linearComponent)
    {
        if (linearComponent > 0)
            return sqrt(linearComponent);
        return 0;
    }

    void Color::writeColor(std::ostream &out, const Color &pixelColor)
    {
        double r = pixelColor.r();
        double g = pixelColor.g();
        double b = pixelColor.b();

        if (r != r)
            r = 0.0;
        if (g != g)
            g = 0.0;
        if (b != b)
            b = 0.0;

        r = linearToGamma(r);
        g = linearToGamma(g);
        b = linearToGamma(b);

        static const Interval intensity(0.000, 0.999);

        int rbyte = int(256 * intensity.clamp(r));
        int gbyte = int(256 * intensity.clamp(g));
        int bbyte = int(256 * intensity.clamp(b));

        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }
};
