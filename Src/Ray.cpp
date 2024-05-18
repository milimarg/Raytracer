/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Ray
*/

#include "Ray.hpp"

namespace rtx
{
    Ray::Ray(const Point3 &origin, const Vec3 &direction)
        : _orig(origin), _dir(direction), _tm(0) {};

    Ray::Ray(const Point3 &origin, const Vec3 &direction, double time)
        : _orig(origin), _dir(direction), _tm(time) {};

    const Point3 &Ray::origin() const
    {
        return _orig;
    }

    const Vec3 &Ray::direction() const
    {
        return _dir;
    }

    Point3 Ray::at(double t) const
    {
        return _orig + t * _dir;
    }
};
