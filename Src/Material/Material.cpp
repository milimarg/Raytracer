/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Material
*/

#include "Material.hpp"

namespace rtx
{
    Color Material::emitted(const Ray &rIn, const HitRecord &rec, double u, double v, const Point3 &p) const
    {
        return Color(0, 0, 0);
    }

    bool Material::scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const
    {
        return false;
    }

    double Material::scatteringPdf(const Ray &RIn, const HitRecord &rec, const Ray &scattered) const
    {
        return 0;
    }
};
