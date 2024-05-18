/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** ConstantMedium
*/

#include "ConstantMedium.hpp"

namespace rtx
{
    ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, double density, std::shared_ptr<Texture> tex)
    : _boundary(boundary), _negInvDensity(-1 / density),
        _phaseFunction(Factory::createMaterial<Isotropic>(tex))
    {}

    ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, double density, const Color &albedo)
    : _boundary(boundary), _negInvDensity(-1 / density),
        _phaseFunction(Factory::createMaterial<Isotropic>(albedo))
    {}

    bool ConstantMedium::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        const bool enableDebug = false;

        HitRecord rec1;
        HitRecord rec2;

        if (!_boundary->hit(r, Interval::_universe, rec1))
            return false;

        if (!_boundary->hit(r, Interval(rec1._t + 0.0001, Math::_infinity), rec2))
            return false;

        if (rec1._t < rayT._min)
            rec1._t = rayT._min;
        if (rec2._t > rayT._max)
            rec2._t = rayT._max;

        if (rec1._t >= rec2._t)
            return false;

        if (rec1._t < 0) rec1._t = 0;

        auto rayLength = r.direction().length();
        auto distanceInsideBoundary = (rec2._t - rec1._t) * rayLength;
        auto hitDistance = _negInvDensity * log(Math::randomDouble());

        if (hitDistance > distanceInsideBoundary)
            return false;

        rec._t = rec1._t + hitDistance / rayLength;
        rec._p = r.at(rec._t);
        rec._normal = Vec3(1,0,0);
        rec._frontFace = true;
        rec._mat = _phaseFunction;
        return true;
    }

    Aabb ConstantMedium::boundingBox() const
    {
        return _boundary->boundingBox();
    }

    double ConstantMedium::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        const Aabb& bbox = _boundary->boundingBox();

        double volume = bbox._x.size() * bbox._y.size() * bbox._z.size();
        return 1.0 / volume;
    }

    Vec3 ConstantMedium::random(const Point3 &origin) const
    {
        const Aabb& bbox = _boundary->boundingBox();

        Point3 minCorner = Point3(bbox._x._min, bbox._y._min, bbox._z._min);
        Point3 maxCorner = Point3(bbox._x._max, bbox._y._max, bbox._z._max);

        double x = Math::randomDouble(minCorner.x(), maxCorner.x());
        double y = Math::randomDouble(minCorner.y(), maxCorner.y());
        double z = Math::randomDouble(minCorner.z(), maxCorner.z());
        return Vec3(x, y, z);
    }
}
