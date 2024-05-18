/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** HittablePdf
*/

#include "HittablePdf.hpp"

namespace rtx
{
    HittablePdf::HittablePdf(const Hittable &objects, const Point3 &origin)
        : _objects(objects), _origin(origin)
    {}

    double HittablePdf::value(const Vec3 &direction) const
    {
        return _objects.pdfValue(_origin, direction);
    }

    Vec3 HittablePdf::generate() const
    {
        return _objects.random(_origin);
    }
};
