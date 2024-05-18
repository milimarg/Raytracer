/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** CheckerTexture
*/

#include "CheckerTexture.hpp"
#include "Factory.hpp"

namespace rtx
{
    CheckerTexture::CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
        : _invScale(1.0 / scale), _even(even), _odd(odd) {}

    CheckerTexture::CheckerTexture(double scale, const Color &c1, const Color &c2)
        : _invScale(1.0 / scale),
        _even(Factory::createTexture<SolidColor>(c1)),
        _odd(Factory::createTexture<SolidColor>(c2))
    {}

    Color CheckerTexture::value(double u, double v, const Point3 &p) const
    {
        auto xInteger = int(std::floor(_invScale * p.x()));
        auto yInteger = int(std::floor(_invScale * p.y()));
        auto zInteger = int(std::floor(_invScale * p.z()));

        bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

        return isEven ? _even->value(u, v, p) : _odd->value(u, v, p);
    }
};
