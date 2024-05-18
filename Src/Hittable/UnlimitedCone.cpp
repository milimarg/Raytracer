/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** UnlimitedCone
*/

#include "UnlimitedCone.hpp"

namespace rtx
{
    UnlimitedCone::UnlimitedCone(
        const Point3 &center,
        std::shared_ptr<Material> mat,
        std::shared_ptr<Texture> normalMap
    ) : _center(center),
    _mat(mat),
    _normalMap(normalMap)
    {
    }

    bool UnlimitedCone::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        Vec3 oc = r.origin() - _center;

        double a = pow(r.direction().x(), 2) - pow(r.direction().y(), 2) + pow(r.direction().z(), 2);
        double b = 2 * (r.direction().x() * oc.x() - r.direction().y() * oc.y() + r.direction().z() * oc.z());
        double c = pow(oc.x(), 2) - pow(oc.y(), 2) + pow(oc.z(), 2);
        double discriminant = pow(b, 2) - 4 * a * c;

        if (discriminant < 0)
            return false;

        double t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (!rayT.surrounds(t)) {
            t = (-b + sqrt(discriminant)) / (2.0 * a);
            if (!rayT.surrounds(t))
                return false;
        }
        if (t < 0)
            return false;
        double y = r.origin().y() + t * r.direction().y();
        Vec3 hitPoint = r.at(t);
        rec._t = t;
        rec._p = hitPoint;
        rec.setFaceNormal(r, hitPoint.normalized());
        if (_normalMap)
            rec.setFaceNormal(r, getNormalFromMap(rec));
        rec._mat = _mat;
        return true;
    }

    Vec3 UnlimitedCone::getNormalFromMap(const HitRecord &rec) const
    {
        double phi = atan2(rec._p.z() - _center.z(), rec._p.x() - _center.x());
        double u = (phi + Math::_pi) / (2 * Math::_pi);
        double v = 0.5;

        Color normalMapColor = _normalMap->value(u, v, rec._p);
        Vec3 normalMapVec = Vec3(normalMapColor.r(), normalMapColor.g(), normalMapColor.b());
        Vec3 perturbedNormal = 2 * normalMapVec - Vec3(1, 1, 1);

        return perturbedNormal;
    }

    Aabb UnlimitedCone::boundingBox() const
    {
        Vec3 minPoint(_center.x() - Math::_infinity, _center.y() - Math::_infinity, _center.z() - Math::_infinity);
        Vec3 maxPoint(_center.x() + Math::_infinity, _center.y() + Math::_infinity, _center.z() + Math::_infinity);

        return Aabb(minPoint, maxPoint);
    }

    double UnlimitedCone::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        return 1.0 / (2 * Math::_pi);
    }

    Vec3 UnlimitedCone::random(const Point3 &origin) const
    {
        Vec3 direction = Vec3::randomUnitVector();
        return direction;
    }

    std::shared_ptr<Hittable> UnlimitedCone::applyTransformation(const Matrix &matrix)
    {
        switch (matrix.getType()) {
            case Matrix::Type::Translation: {
                _center = _center * matrix;
                break;
            }

            case Matrix::Type::RotationX:
            case Matrix::Type::RotationY:
            case Matrix::Type::RotationZ: {
                break;
            }

            case Matrix::Type::Scale: {
                break;
            }

            case Matrix::Type::ShearX:
            case Matrix::Type::ShearY:
            case Matrix::Type::ShearZ: {
                break;
            }
        }
        return Factory::createHittable<UnlimitedCone>(_center, _mat);
    }
}
