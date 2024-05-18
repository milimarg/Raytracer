/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** SpherePdf
*/

#include "SpherePdf.hpp"

namespace rtx
{
    double SpherePdf::value(const Vec3 &direction) const
    {
        return 1 / (4 * Math::_pi);
    }

    Vec3 SpherePdf::generate() const
    {
        return Vec3::randomUnitVector();
    }
};
