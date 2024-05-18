/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** MixturePdf
*/

#include "MixturePdf.hpp"

namespace rtx
{
    MixturePdf::MixturePdf(std::shared_ptr<Pdf> p0, std::shared_ptr<Pdf> p1)
    {
        _p[0] = p0;
        _p[1] = p1;
    }

    double MixturePdf::value(const Vec3 &direction) const
    {
        return 0.5 * _p[0]->value(direction) + 0.5 * _p[1]->value(direction);
    }

    Vec3 MixturePdf::generate() const
    {
        if (Math::randomDouble() < 0.5)
            return _p[0]->generate();
        else
            return _p[1]->generate();
    }
};
