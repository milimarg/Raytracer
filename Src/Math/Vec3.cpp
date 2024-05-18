/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Vec3.cpp
*/

#include "Vec3.hpp"
#include "Math/Matrix/Matrix.hpp"
#include "Point3.hpp"

namespace rtx
{
    Vec3::Vec3()
        : _e{0, 0, 0, 1}
    {}

    Vec3::Vec3(double e0, double e1, double e2)
        : _e{e0, e1, e2, 1}
    {}

    Vec3::~Vec3()
    {}

    Vec3::Vec3(const Point3 &v)
        : _e{v.x(), v.y(), v.z(), v.w()}
    {}

    double Vec3::x() const
    {
        return _e[0];
    }

    double Vec3::y() const
    {
        return _e[1];
    }

    double Vec3::z() const
    {
        return _e[2];
    }

    double Vec3::w() const
    {
        return _e[3];
    }

    Vec3 Vec3::operator-() const
    {
        return Vec3(-_e[0], -_e[1], -_e[2]);
    }

    double Vec3::operator[](int i) const
    {
        return _e[i];
    }

    double &Vec3::operator[](int i)
    {
        return _e[i];
    }

    Vec3 &Vec3::operator+=(const Vec3 &v)
    {
        _e[0] += v._e[0];
        _e[1] += v._e[1];
        _e[2] += v._e[2];
        return *this;
    }

    Vec3 &Vec3::operator+=(const Point3 &v)
    {
        _e[0] += v._e[0];
        _e[1] += v._e[1];
        _e[2] += v._e[2];
        return *this;
    }

    Vec3 &Vec3::operator*=(double t)
    {
        _e[0] *= t;
        _e[1] *= t;
        _e[2] *= t;
        return *this;
    }

    Vec3 &Vec3::operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double Vec3::length() const
    {
        return sqrt(lengthSquared());
    }

    double Vec3::lengthSquared() const
    {
        return _e[0] * _e[0] + _e[1] * _e[1] + _e[2] * _e[2];
    }

    bool Vec3::nearZero() const
    {
        auto s = 1e-8;
        return (std::fabs(_e[0]) < s) && (std::fabs(_e[1]) < s) && (std::fabs(_e[2]) < s);
    }

    Vec3 Vec3::rotate(double angle, const Vec3 &axis) const
    {
        double radians = Math::degreesToRadians(angle);
        double c = cos(radians);
        double s = sin(radians);
        double t = 1.0 - c;

        double x = _e[0];
        double y = _e[1];
        double z = _e[2];
        double u = axis._e[0];
        double v = axis._e[1];
        double w = axis._e[2];

        double xNew = (t * u * u + c) * x + (t * u * v - s * w) * y + (t * u * w + s * v) * z;
        double yNew = (t * u * v + s * w) * x + (t * v * v + c) * y + (t * v * w - s * u) * z;
        double zNew = (t * u * w - s * v) * x + (t * v * w + s * u) * y + (t * w * w + c) * z;

        return Vec3(xNew, yNew, zNew);
    }

    Vec3 Vec3::random()
    {
        return Vec3(Math::randomDouble(), Math::randomDouble(), Math::randomDouble());
    }

    Vec3 Vec3::random(double min, double max)
    {
        return Vec3(Math::randomDouble(min,max), Math::randomDouble(min,max), Math::randomDouble(min,max));
    }

    std::ostream &operator<<(std::ostream &out, const Vec3 &v)
    {
        return out << v._e[0] << ' ' << v._e[1] << ' ' << v._e[2] << " (" << v._e[3] << ")";
    }

    Vec3 operator+(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u._e[0] + v._e[0], u._e[1] + v._e[1], u._e[2] + v._e[2]);
    }

    Vec3 operator+(const Vec3 &u, const Point3 &v)
    {
        return Vec3(u._e[0] + v._e[0], u._e[1] + v._e[1], u._e[2] + v._e[2]);
    }

    Vec3 operator-(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u._e[0] - v._e[0], u._e[1] - v._e[1], u._e[2] - v._e[2]);
    }

    Vec3 operator-(const Vec3 &u, const Point3 &v)
    {
        return Vec3(u._e[0] - v._e[0], u._e[1] - v._e[1], u._e[2] - v._e[2]);
    }

    Vec3 operator*(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u._e[0] * v._e[0], u._e[1] * v._e[1], u._e[2] * v._e[2]);
    }

    Vec3 operator*(const Vec3 &u, const Point3 &v)
    {
        return Vec3(u._e[0] * v._e[0], u._e[1] * v._e[1], u._e[2] * v._e[2]);
    }

    Vec3 operator*(double t, const Vec3 &v)
    {
        return Vec3(t*v._e[0], t*v._e[1], t*v._e[2]);
    }

    Vec3 operator*(const Vec3 &v, double t)
    {
        return t * v;
    }

    Vec3 operator*(const Vec3 &v, const Matrix &m)
    {
        Vec3 result;

        result[0] = v.x() * m._data[0][0] + v.y() * m._data[1][0] + v.z() * m._data[2][0] + v.w() * m._data[3][0];
        result[1] = v.x() * m._data[0][1] + v.y() * m._data[1][1] + v.z() * m._data[2][1] + v.w() * m._data[3][1];
        result[2] = v.x() * m._data[0][2] + v.y() * m._data[1][2] + v.z() * m._data[2][2] + v.w() * m._data[3][2];
        result[3] = v.x() * m._data[0][0] + v.y() * m._data[1][3] + v.z() * m._data[2][3] + v.w() * m._data[3][3];

        return result;
    }

    Vec3 operator/(const Vec3 &v, double t)
    {
        return (1/t) * v;
    }

    double Vec3::dot(const Vec3 &u, const Vec3 &v)
    {
        return u._e[0] * v._e[0]
            + u._e[1] * v._e[1]
            + u._e[2] * v._e[2];
    }

    double Vec3::dot(const Vec3 &u, const Point3 &v)
    {
        return u._e[0] * v._e[0]
            + u._e[1] * v._e[1]
            + u._e[2] * v._e[2];
    }

    Vec3 Vec3::cross(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u._e[1] * v._e[2] - u._e[2] * v._e[1],
                    u._e[2] * v._e[0] - u._e[0] * v._e[2],
                    u._e[0] * v._e[1] - u._e[1] * v._e[0]);
    }

    Vec3 Vec3::cross(const Vec3 &u, const Point3 &v)
    {
        return Vec3(u._e[1] * v._e[2] - u._e[2] * v._e[1],
                    u._e[2] * v._e[0] - u._e[0] * v._e[2],
                    u._e[0] * v._e[1] - u._e[1] * v._e[0]);
    }

    Vec3 Vec3::unitVector(const Vec3 &v)
    {
        return v / v.length();
    }

    Vec3 Vec3::unitVector(const Point3 &v)
    {
        return v / v.length();
    }

    Vec3 Vec3::randomInUnitDisk()
    {
        while (true) {
            auto p = Vec3(Math::randomDouble(-1, 1), Math::randomDouble(-1, 1), 0);
            if (p.lengthSquared() < 1)
                return p;
        }
    }

    Vec3 Vec3::randomInUnitSphere()
    {
        while (true) {
            auto p = Vec3::random(-1,1);
            if (p.lengthSquared() < 1)
                return p;
        }
    }

    Vec3 Vec3::randomUnitVector()
    {
        return unitVector(randomInUnitSphere());
    }

    Vec3 Vec3::randomOnHemisphere(const Vec3 &normal)
    {
        Vec3 onUnitSphere = randomUnitVector();
        if (dot(onUnitSphere, normal) > 0.0)
            return onUnitSphere;
        else
            return -onUnitSphere;
    }

    Vec3 Vec3::randomOnHemisphere(const Point3 &normal)
    {
        Vec3 onUnitSphere = randomUnitVector();
        if (dot(onUnitSphere, normal) > 0.0)
            return onUnitSphere;
        else
            return -onUnitSphere;
    }

    Vec3 Vec3::reflect(const Vec3 &v, const Vec3 &n)
    {
        return v - 2 * dot(v, n) * n;
    }

    Vec3 Vec3::reflect(const Vec3 &v, const Point3 &n)
    {
        return v - 2 * dot(v, n) * n;
    }

    Vec3 Vec3::refract(const Vec3 &uv, const Vec3 &n, double etaiOverEtat)
    {
        auto cosTheta = fmin(dot(-uv, n), 1.0);
        Vec3 rOutPerp =  etaiOverEtat * (uv + cosTheta*n);
        Vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.lengthSquared())) * n;
        return rOutPerp + rOutParallel;
    }

    Vec3 Vec3::refract(const Vec3 &uv, const Point3 &n, double etaiOverEtat)
    {
        auto cosTheta = fmin(dot(-uv, n), 1.0);
        Vec3 rOutPerp =  etaiOverEtat * (uv + cosTheta*n);
        Vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.lengthSquared())) * n;
        return rOutPerp + rOutParallel;
    }

    Vec3 Vec3::randomCosineDirection()
    {
        auto r1 = Math::randomDouble();
        auto r2 = Math::randomDouble();

        auto phi = 2 * Math::_pi * r1;
        auto x = cos(phi) * sqrt(r2);
        auto y = sin(phi) * sqrt(r2);
        auto z = sqrt(1 - r2);

        return Vec3(x, y, z);
    }

    Vec3 Vec3::normalized() const
    {
        float length = std::sqrt(x() * x() + y() * y() + z() * z());
        return Vec3(x() / length, y() / length, z() / length);
    }

    float Vec3::distance(const Vec3 &self, const Vec3 &other)
    {
        float dx = self.x() - other.x();
        float dy = self.y() - other.y();
        float dz = self.z() - other.z();
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};
