/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Color
*/

#ifndef COLOR_HPP_
    #define COLOR_HPP_
    #include "Vec3.hpp"

namespace rtx
{
    class Matrix;
    class Vec3;

    class Color {
        public:
            double _e[4];

            Color();
            Color(double e0, double e1, double e2);
            ~Color();

            double r() const;
            double g() const;
            double b() const;
            double a() const;

            Color operator-() const;
            double operator[](int i) const;
            double &operator[](int i);
            Color &operator+=(const Color &v);
            Color &operator*=(double t);
            Color &operator/=(double t);

            double length() const;
            double lengthSquared() const;
            bool nearZero() const;
            static Color random();
            static Color random(double min, double max);

            static double linearToGamma(double linearComponent);
            static void writeColor(std::ostream &out, const Color &pixelColor);

        private:
    };

    std::ostream &operator<<(std::ostream &out, const Color &v);
    Color operator+(const Color &u, const Color &v);
    Color operator-(const Color &u, const Color &v);
    Color operator*(const Color &u, const Color &v);
    Color operator*(double t, const Color &v);
    Color operator*(const Color &v, double t);
    Color operator*(const Color &v, const Matrix &matrix);
    Color operator/(const Color &v, double t);
};

#endif /* !COLOR_HPP_ */
