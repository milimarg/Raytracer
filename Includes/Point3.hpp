/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Point3
*/

#ifndef POINT3_HPP_
    #define POINT3_HPP_
    #include <cmath>
    #include <iostream>
    #include "Math/Math.hpp"

namespace rtx
{
    class Matrix;
    class Vec3;

    class Point3 {
        public:
            double _e[4];

            Point3();
            Point3(double e0, double e1, double e2);
            ~Point3();

            Point3(const Vec3 &v);

            double x() const;
            double y() const;
            double z() const;
            double w() const;

            Point3 operator-() const;
            double operator[](int i) const;
            double &operator[](int i);
            Point3 &operator+=(const Point3 &v);
            Point3 &operator+=(const Vec3 &v);
            Point3 &operator*=(double t);
            Point3 &operator/=(double t);

            bool operator==(Point3 p);
            bool operator==(const Point3 &p);
            bool operator==(const Point3 &p) const;

            double length() const;
            double lengthSquared() const;
            bool nearZero() const;
            static Point3 random();
            static Point3 random(double min, double max);

            static double dot(const Point3 &u, const Point3 &v);
            static Point3 cross(const Point3 &u, const Point3 &v);
            static Point3 unitVector(const Point3 &v);
            static Point3 randomInUnitDisk();
            static Point3 randomInUnitSphere();
            static Point3 randomUnitVector();
            static Point3 randomOnHemisphere(const Point3 &normal);
            static Point3 reflect(const Point3 &v, const Point3 &n);
            static Point3 refract(const Point3 &uv, const Point3 &n, double etaiOverEtat);
            static Point3 randomCosineDirection();

            static double dot(const Point3 &u, const Vec3 &v);
            static Point3 cross(const Point3 &u, const Vec3 &v);
            static Point3 unitVector(const Vec3 &v);
            static Point3 randomOnHemisphere(const Vec3 &normal);
            static Point3 reflect(const Point3 &v, const Vec3 &n);
            static Point3 refract(const Point3 &uv, const Vec3 &n, double etaiOverEtat);

        private:
    };

    std::ostream &operator<<(std::ostream &out, const Point3 &v);
    Point3 operator+(const Point3 &u, const Point3 &v);
    Point3 operator-(const Point3 &u, const Point3 &v);
    Point3 operator*(const Point3 &u, const Point3 &v);
    Point3 operator*(double t, const Point3 &v);
    Point3 operator*(const Point3 &v, double t);
    Point3 operator*(const Point3 &v, const Matrix &matrix);
    Point3 operator/(const Point3 &v, double t);

    Point3 operator+(const Point3 &u, const Vec3 &v);
    Point3 operator-(const Point3 &u, const Vec3 &v);
    Point3 operator*(const Point3 &u, const Vec3 &v);
};

#endif /* !POINT3_HPP_ */
