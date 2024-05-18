/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** DiffuseLight
*/

#include "DiffuseLight.hpp"
#include "SolidColor.hpp"
#include "ImageTexture.hpp"
#include "Factory.hpp"

namespace rtx
{
    DiffuseLight::DiffuseLight(std::shared_ptr<Texture> tex)
        : _tex(tex) {}

    DiffuseLight::DiffuseLight(const Color &emit)
       : _tex(Factory::createTexture<SolidColor>(emit)) {}

    Color DiffuseLight::emitted(const Ray &rIn, const HitRecord &rec, double u, double v, const Point3 &p) const
    {
        if (!rec._frontFace)
            return Color(0, 0, 0);

        std::shared_ptr<ImageTexture> ptr = std::dynamic_pointer_cast<ImageTexture>(_tex);

        if (ptr) {
            ptr->setRotationAngleX(0);
            ptr->setRotationAngleY(0);
        }
        return _tex->value(u, v, p);
    }
};
