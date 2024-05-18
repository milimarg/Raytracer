/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Ray
*/

#ifndef RAY_HPP_
    #define RAY_HPP_
    #include "Vec3.hpp"
    #include "Point3.hpp"

namespace rtx
{
    class Ray {
        public:
            Ray() = default;
            Ray(const Point3 &origin, const Vec3 &direction);
            Ray(const Point3 &origin, const Vec3 &direction, double time);

            const Point3 &origin() const;
            const Vec3 &direction() const;
            double time() const { return _tm; }
            Point3 at(double t) const;

        private:
            Point3 _orig;
            Vec3 _dir;
            double _tm;
    };
};

#endif /* !RAY_HPP_ */
