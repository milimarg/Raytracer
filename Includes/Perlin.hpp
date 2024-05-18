/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Perlin
*/

#ifndef PERLIN_HPP_
    #define PERLIN_HPP_
    #include "Vec3.hpp"
    #include "Point3.hpp"

namespace rtx
{
    class Perlin {
        public:
            Perlin();
            ~Perlin();

            double noise(const Point3 &p) const;
            double turb(const Point3 &p, int depth) const;

        private:
            static const int _pointCount = 256;
            Vec3 *_randvec;
            int *_permX;
            int *_permY;
            int *_permZ;

            static int *perlinGeneratePerm();
            static void permute(int *p, int n);
            static double perlinInterp(const Vec3 c[2][2][2], double u, double v, double w);
    };
};

#endif /*!PERLIN_HPP_ */
