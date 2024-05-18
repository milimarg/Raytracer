/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Point3
*/

#include "Point3.hpp"
#include "Math/Matrix/Matrix.hpp"
#include "Vec3.hpp"

namespace rtx
{
    Point3::Point3()
        : _e{0, 0, 0, 1}
    {}

    Point3::Point3(double e0, double e1, double e2)
        : _e{e0, e1, e2, 1}
    {}

    Point3::~Point3()
    {}

    Point3::Point3(const Vec3 &v)
        : _e{v.x(), v.y(), v.z(), v.w()}
    {}

    double Point3::x() const
    {
        return _e[0];
    }

    double Point3::y() const
    {
        return _e[1];
    }

    double Point3::z() const
    {
        return _e[2];
    }

    double Point3::w() const
    {
        return _e[3];
    }

    Point3 Point3::operator-() const
    {
        return Point3(-_e[0], -_e[1], -_e[2]);
    }

    double Point3::operator[](int i) const
    {
        return _e[i];
    }

    double &Point3::operator[](int i)
    {
        return _e[i];
    }

    Point3 &Point3::operator+=(const Point3 &v)
    {
        _e[0] += v._e[0];
        _e[1] += v._e[1];
        _e[2] += v._e[2];
        return *this;
    }

    Point3 &Point3::operator+=(const Vec3 &v)
    {
        _e[0] += v._e[0];
        _e[1] += v._e[1];
        _e[2] += v._e[2];
        return *this;
    }

    Point3 &Point3::operator*=(double t)
    {
        _e[0] *= t;
        _e[1] *= t;
        _e[2] *= t;
        return *this;
    }

    Point3 &Point3::operator/=(double t)
    {
        return *this *= 1 / t;
    }

    bool Point3::operator==(Point3 p)
    {
        return x() == p.x() && y() == p.y() && z() == p.z();
    }

    bool Point3::operator==(const Point3 &p)
    {
        return x() == p.x() && y() == p.y() && z() == p.z();
    }

    bool Point3::operator==(const Point3 &p) const
    {
        return x() == p.x() && y() == p.y() && z() == p.z();
    }

    double Point3::length() const
    {
        return sqrt(lengthSquared());
    }

    double Point3::lengthSquared() const
    {
        return _e[0] * _e[0] + _e[1] * _e[1] + _e[2] * _e[2];
    }

    bool Point3::nearZero() const
    {
        auto s = 1e-8;
        return (std::fabs(_e[0]) < s) && (std::fabs(_e[1]) < s) && (std::fabs(_e[2]) < s);
    }

    Point3 Point3::random()
    {
        return Point3(Math::randomDouble(), Math::randomDouble(), Math::randomDouble());
    }

    Point3 Point3::random(double min, double max)
    {
        return Point3(Math::randomDouble(min,max), Math::randomDouble(min,max), Math::randomDouble(min,max));
    }

    std::ostream &operator<<(std::ostream &out, const Point3 &v)
    {
        return out << v._e[0] << ' ' << v._e[1] << ' ' << v._e[2];
    }

    Point3 operator+(const Point3 &u, const Point3 &v)
    {
        return Point3(u._e[0] + v._e[0], u._e[1] + v._e[1], u._e[2] + v._e[2]);
    }

    Point3 operator+(const Point3 &u, const Vec3 &v)
    {
        return Point3(u._e[0] + v._e[0], u._e[1] + v._e[1], u._e[2] + v._e[2]);
    }

    Point3 operator-(const Point3 &u, const Point3 &v)
    {
        return Point3(u._e[0] - v._e[0], u._e[1] - v._e[1], u._e[2] - v._e[2]);
    }

    Point3 operator-(const Point3 &u, const Vec3 &v)
    {
        return Point3(u._e[0] - v._e[0], u._e[1] - v._e[1], u._e[2] - v._e[2]);
    }

    Point3 operator*(const Point3 &u, const Point3 &v)
    {
        return Point3(u._e[0] * v._e[0], u._e[1] * v._e[1], u._e[2] * v._e[2]);
    }

    Point3 operator*(const Point3 &u, const Vec3 &v)
    {
        return Point3(u._e[0] * v._e[0], u._e[1] * v._e[1], u._e[2] * v._e[2]);
    }

    Point3 operator*(double t, const Point3 &v)
    {
        return Point3(t*v._e[0], t*v._e[1], t*v._e[2]);
    }

    Point3 operator*(const Point3 &v, double t)
    {
        return t * v;
    }

    Point3 operator*(const Point3 &v, const Matrix &m)
    {
        Point3 result;

        result[0] = v.x() * m._data[0][0] + v.y() * m._data[1][0] + v.z() * m._data[2][0] + v.w() * m._data[3][0];
        result[1] = v.x() * m._data[0][1] + v.y() * m._data[1][1] + v.z() * m._data[2][1] + v.w() * m._data[3][1];
        result[2] = v.x() * m._data[0][2] + v.y() * m._data[1][2] + v.z() * m._data[2][2] + v.w() * m._data[3][2];
        result[3] = v.x() * m._data[0][0] + v.y() * m._data[1][3] + v.z() * m._data[2][3] + v.w() * m._data[3][3];
        return result;
    }

    Point3 operator/(const Point3 &v, double t)
    {
        return (1/t) * v;
    }

    double Point3::dot(const Point3 &u, const Point3 &v)
    {
        return u._e[0] * v._e[0]
            + u._e[1] * v._e[1]
            + u._e[2] * v._e[2];
    }

    double Point3::dot(const Point3 &u, const Vec3 &v)
    {
        return u._e[0] * v._e[0]
            + u._e[1] * v._e[1]
            + u._e[2] * v._e[2];
    }

    Point3 Point3::cross(const Point3 &u, const Point3 &v)
    {
        return Point3(u._e[1] * v._e[2] - u._e[2] * v._e[1],
                    u._e[2] * v._e[0] - u._e[0] * v._e[2],
                    u._e[0] * v._e[1] - u._e[1] * v._e[0]);
    }

    Point3 Point3::cross(const Point3 &u, const Vec3 &v)
    {
        return Point3(u._e[1] * v._e[2] - u._e[2] * v._e[1],
                    u._e[2] * v._e[0] - u._e[0] * v._e[2],
                    u._e[0] * v._e[1] - u._e[1] * v._e[0]);
    }

    Point3 Point3::unitVector(const Point3 &v)
    {
        return v / v.length();
    }

    Point3 Point3::unitVector(const Vec3 &v)
    {
        return v / v.length();
    }

    Point3 Point3::randomInUnitDisk()
    {
        while (true) {
            auto p = Point3(Math::randomDouble(-1, 1), Math::randomDouble(-1, 1), 0);
            if (p.lengthSquared() < 1)
                return p;
        }
    }

    Point3 Point3::randomInUnitSphere()
    {
        while (true) {
            auto p = Point3::random(-1,1);
            if (p.lengthSquared() < 1)
                return p;
        }
    }

    Point3 Point3::randomUnitVector()
    {
        return unitVector(randomInUnitSphere());
    }

    Point3 Point3::randomOnHemisphere(const Point3 &normal)
    {
        Point3 onUnitSphere = randomUnitVector();
        if (dot(onUnitSphere, normal) > 0.0)
            return onUnitSphere;
        else
            return -onUnitSphere;
    }

    Point3 Point3::randomOnHemisphere(const Vec3 &normal)
    {
        Point3 onUnitSphere = randomUnitVector();
        if (dot(onUnitSphere, normal) > 0.0)
            return onUnitSphere;
        else
            return -onUnitSphere;
    }

    Point3 Point3::reflect(const Point3 &v, const Point3 &n)
    {
        return v - 2 * dot(v, n) * n;
    }

    Point3 Point3::reflect(const Point3 &v, const Vec3 &n)
    {
        return v - 2 * dot(v, n) * n;
    }

    Point3 Point3::refract(const Point3& uv, const Point3& n, double etaiOverEtat)
    {
        auto cosTheta = fmin(dot(-uv, n), 1.0);
        Point3 rOutPerp =  etaiOverEtat * (uv + cosTheta*n);
        Point3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.lengthSquared())) * n;
        return rOutPerp + rOutParallel;
    }

    Point3 Point3::refract(const Point3& uv, const Vec3& n, double etaiOverEtat)
    {
        auto cosTheta = fmin(dot(-uv, n), 1.0);
        Point3 rOutPerp =  etaiOverEtat * (uv + cosTheta*n);
        Point3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.lengthSquared())) * n;
        return rOutPerp + rOutParallel;
    }

    Point3 Point3::randomCosineDirection()
    {
        auto r1 = Math::randomDouble();
        auto r2 = Math::randomDouble();

        auto phi = 2*Math::_pi * r1;
        auto x = cos(phi) * sqrt(r2);
        auto y = sin(phi) * sqrt(r2);
        auto z = sqrt(1 - r2);

        return Point3(x, y, z);
    }
};
