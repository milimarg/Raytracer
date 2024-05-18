/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** CosinePdf
*/

#include "CosinePdf.hpp"

namespace rtx
{
    CosinePdf::CosinePdf(const Vec3 &w)
    {
        _uvw.buildFromW(w);
    }

    double CosinePdf::value(const Vec3 &direction) const
    {
        auto cosineTheta = Vec3::dot(Vec3::unitVector(direction), _uvw.w());
        return fmax(0, cosineTheta / Math::_pi);
    }

    Vec3 CosinePdf::generate() const
    {
        return _uvw.local(Vec3::randomCosineDirection());
    }
};
