/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Aabb
*/

#ifndef AABB_HPP_
    #define AABB_HPP_
    #include "Interval.hpp"
    #include "Vec3.hpp"
    #include "Ray.hpp"

namespace rtx
{
    class Aabb {
        public:
            Interval _x;
            Interval _y;
            Interval _z;

            Aabb() = default;

            Aabb(const Interval &x, const Interval &y, const Interval &z);

            Aabb(const Point3 &a, const Point3 &b);

            Aabb(const Aabb &box0, const Aabb &box1);

            const Interval &axisInterval(int n) const;

            bool hit(const Ray &r, Interval ray_t) const;

            int longestAxis();

            static const Aabb _empty;
            static const Aabb _universe;

        private:
            void padToMinimums();
    };

    Aabb operator+(const Aabb &bbox, const Vec3 &offset);
    Aabb operator+(const Vec3 &offset, const Aabb &bbox);
};

#endif /* !AABB_HPP_ */
