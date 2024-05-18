/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Metal
*/

#include "Metal.hpp"

namespace rtx
{
    Metal::Metal(const Color &albedo, double fuzz)
        : _albedo(albedo), _fuzz(fuzz < 1 ? fuzz : 1) {}

    bool Metal::scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const
    {
        Vec3 reflected = Vec3::reflect(rIn.direction(), rec._normal);
        reflected = Vec3::unitVector(reflected) + (_fuzz * Vec3::randomUnitVector());

        srec._attenuation = _albedo;
        srec._pdfPtr = nullptr;
        srec._skipPdf = true;
        srec._skipPdfRay = Ray(rec._p, reflected, rIn.time());

        return true;
    }
};
