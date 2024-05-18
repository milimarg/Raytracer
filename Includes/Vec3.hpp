/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Vec3
*/

#ifndef VEC3_HPP_
    #define VEC3_HPP_
    #include <cmath>
    #include <iostream>
    #include "Math/Math.hpp"

namespace rtx
{
    class Matrix;
    class Point3;

    class Vec3 {
        public:
            double _e[4];

            Vec3();
            Vec3(double e0, double e1, double e2);
            ~Vec3();

            Vec3(const Point3 &v);

            double x() const;
            double y() const;
            double z() const;
            double w() const;

            Vec3 operator-() const;
            double operator[](int i) const;
            double &operator[](int i);
            Vec3 &operator+=(const Vec3 &v);
            Vec3 &operator+=(const Point3 &v);
            Vec3 &operator*=(double t);
            Vec3 &operator/=(double t);

            double length() const;
            double lengthSquared() const;
            bool nearZero() const;
            Vec3 rotate(double angle, const Vec3 &axis) const;
            Vec3 normalized() const;

            static Vec3 random();
            static Vec3 random(double min, double max);

            static double dot(const Vec3 &u, const Vec3 &v);
            static Vec3 cross(const Vec3 &u, const Vec3 &v);
            static Vec3 unitVector(const Vec3 &v);
            static Vec3 randomInUnitDisk();
            static Vec3 randomInUnitSphere();
            static Vec3 randomUnitVector();
            static Vec3 randomOnHemisphere(const Vec3 &normal);
            static Vec3 reflect(const Vec3 &v, const Vec3 &n);
            static Vec3 refract(const Vec3 &uv, const Vec3 &n, double etaiOverEtat);
            static Vec3 randomCosineDirection();

            static double dot(const Vec3 &u, const Point3 &v);
            static Vec3 cross(const Vec3 &u, const Point3 &v);
            static Vec3 unitVector(const Point3 &v);
            static Vec3 randomOnHemisphere(const Point3 &normal);
            static Vec3 reflect(const Vec3 &v, const Point3 &n);
            static Vec3 refract(const Vec3 &uv, const Point3 &n, double etaiOverEtat);
            static float distance(const Vec3& self, const Vec3& other);

        private:
    };

    std::ostream &operator<<(std::ostream &out, const Vec3 &v);
    Vec3 operator+(const Vec3 &u, const Vec3 &v);
    Vec3 operator-(const Vec3 &u, const Vec3 &v);
    Vec3 operator*(const Vec3 &u, const Vec3 &v);
    Vec3 operator*(double t, const Vec3 &v);
    Vec3 operator*(const Vec3 &v, double t);
    Vec3 operator*(const Vec3 &v, const Matrix &matrix);
    Vec3 operator/(const Vec3 &v, double t);

    Vec3 operator+(const Vec3 &u, const Point3 &v);
    Vec3 operator-(const Vec3 &u, const Point3 &v);
    Vec3 operator*(const Vec3 &u, const Point3 &v);
};

#endif /* !VEC3_HPP_ */
