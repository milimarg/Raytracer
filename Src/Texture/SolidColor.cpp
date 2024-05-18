/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** SolidColor
*/

#include "SolidColor.hpp"

namespace rtx
{
    SolidColor::SolidColor(const Color &albedo)
        : _albedo(albedo) {}

    SolidColor::SolidColor(double red, double green, double blue)
        : SolidColor(Color(red, green, blue)) {}

    Color SolidColor::value(double u, double v, const Point3 &p) const
    {
        return _albedo;
    }
};
