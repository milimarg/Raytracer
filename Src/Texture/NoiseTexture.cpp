/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** NoiseTexture
*/

#include "NoiseTexture.hpp"

namespace rtx
{
    NoiseTexture::NoiseTexture(double scale, int type)
        : _scale(scale), _type(type)
    {}

    Color NoiseTexture::value(double u, double v, const Point3 &p) const
    {
        switch (_type) {
            case 0:
                return Color(1, 1, 1) * 0.5 * (1.0 + _noise.noise(_scale * p));
                break;
            case 1:
                return Color(1, 1, 1) * _noise.turb(p, 7);
                break;
            case 2:
                return Color(0.5, 0.5, 0.5) * (1 + sin(_scale * p.z() + 10 * _noise.turb(p, 7)));
                break;
            default:
                return Color(0.5, 0.5, 0.5) * (1 + sin(_scale * p.z() + 10 * _noise.turb(p, 7)));
                break;
        }
    }
};
