/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Lambertian
*/

#include "Lambertian.hpp"
#include "CosinePdf.hpp"
#include "SolidColor.hpp"
#include "Factory.hpp"

namespace rtx
{
    Lambertian:: Lambertian(const Color &albedo)
        : _tex(Factory::createTexture<SolidColor>(albedo)) {}

    Lambertian::Lambertian(std::shared_ptr<Texture> tex)
        : _tex(tex) {}

    bool Lambertian::scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const
    {
        srec._attenuation = _tex->value(rec._u, rec._v, rec._p);
        srec._pdfPtr = Factory::createPdf<CosinePdf>(rec._normal);
        srec._skipPdf = false;
        return true;
    }

    double Lambertian::scatteringPdf(const Ray & rIn, const HitRecord &rec, const Ray &scattered) const
    {
        auto cosTheta = Vec3::dot(rec._normal, Vec3::unitVector(scattered.direction()));
        return cosTheta < 0 ? 0 : cosTheta / Math::_pi;
    }
}
