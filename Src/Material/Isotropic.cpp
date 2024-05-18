/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Isotropic
*/

#include "Isotropic.hpp"
#include "SpherePdf.hpp"
#include "SolidColor.hpp"
#include "Factory.hpp"

namespace rtx
{
    Isotropic::Isotropic(const Color &albedo)
        : _tex(Factory::createTexture<SolidColor>(albedo)) {}

    Isotropic::Isotropic(std::shared_ptr<Texture> tex)
        : _tex(tex) {}

    bool Isotropic::scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const
    {
        srec._attenuation = _tex->value(rec._u, rec._v, rec._p);
        srec._pdfPtr = Factory::createPdf<SpherePdf>();
        srec._skipPdf = false;
        return true;
    }

    double Isotropic::scatteringPdf(const Ray &rIn, const HitRecord& rec, const Ray &scattered) const
    {
        return 1 / (4 * Math::_pi);
    }
};
