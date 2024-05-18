/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Dielectric
*/

#include "Dielectric.hpp"

namespace rtx
{
    Dielectric::Dielectric(double refractionIndex)
        : _refractionIndex(refractionIndex) {}

    bool Dielectric::scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const
    {
        srec._attenuation = Color(1.0, 1.0, 1.0);
        srec._pdfPtr = nullptr;
        srec._skipPdf = true;
        double ri = rec._frontFace ? (1.0 / _refractionIndex) : _refractionIndex;

        Vec3 unitDirection = Vec3::unitVector(rIn.direction());
        double cosTheta = fmin(Vec3::dot(-unitDirection, rec._normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = ri * sinTheta > 1.0;
        Vec3 direction;

        if (cannotRefract || reflectance(cosTheta, ri) > Math::randomDouble())
            direction = Vec3::reflect(unitDirection, rec._normal);
        else
            direction = Vec3::refract(unitDirection, rec._normal, ri);

        srec._skipPdfRay = Ray(rec._p, direction, rIn.time());
        return true;
    }

    double Dielectric::reflectance(double cosine, double refractionIndex)
    {
        auto r0 = pow((1 - refractionIndex) / (1 + refractionIndex) , 2);
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};
