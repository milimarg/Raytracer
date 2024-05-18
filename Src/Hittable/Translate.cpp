/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Translate
*/

#include "Translate.hpp"

namespace rtx
{
    Translate::Translate(std::shared_ptr<Hittable> object, const Vec3 &offset)
        : _object(object), _offset(offset)
    {
        _bbox = object->boundingBox() + offset;
    }

    bool Translate::hit(const Ray &r, Interval ray_t, HitRecord &rec) const
    {
        Ray offsetR(r.origin() - _offset, r.direction(), r.time());

        if (!_object->hit(offsetR, ray_t, rec))
            return false;

        rec._p += _offset;

        return true;
    }

    Aabb Translate::boundingBox() const
    {
        return _bbox;
    }

    double Translate::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        return _object->pdfValue(origin - _offset, direction);
    }

    Vec3 Translate::random(const Point3 &origin) const
    {
        return _object->random(origin - _offset);
    }
};
