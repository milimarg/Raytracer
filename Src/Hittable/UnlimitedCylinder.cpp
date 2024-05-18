/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** UnlimitedCylinder
*/

#include "UnlimitedCylinder.hpp"
#include "Math/Matrix/Matrix.hpp"
#include "Factory.hpp"

namespace rtx
{
    UnlimitedCylinder::UnlimitedCylinder(
        const Point3 &center,
        double radius,
        std::shared_ptr<Material> mat,
        std::shared_ptr<Texture> normalMap
    ) : _center(center),
    _radius(radius),
    _mat(mat),
    _normalMap(normalMap)
    {
    }

    bool UnlimitedCylinder::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        Vec3 oc = r.origin() - _center;
        double a = pow(r.direction().x(), 2) + pow(r.direction().z(), 2);
        double b = 2 * (oc.x() * r.direction().x() + oc.z() * r.direction().z());
        double c = pow(oc.x(), 2) + pow(oc.z(), 2)  - pow(_radius, 2);

        double discriminant = pow(b, 2) - 4.0 * a * c;

        if (discriminant < 0)
            return false;
        double t = (-b - sqrt(discriminant)) / (2 * a);
        if (!rayT.surrounds(t)) {
            t = (-b + sqrt(discriminant)) / (2 * a);
            if (!rayT.surrounds(t))
                return false;
        }
        if (t < 0)
            return false;
        Vec3 hitPoint = r.at(t);
        rec._t = t;
        rec._p = r.at(t);
        rec.setFaceNormal(r, hitPoint.normalized());
        if (_normalMap)
            rec.setFaceNormal(r, getNormalFromMap(rec));
        rec._mat = _mat;
        return true;
    }

    Vec3 UnlimitedCylinder::getNormalFromMap(const HitRecord &rec) const
    {
        double phi = atan2(rec._p.z() - _center.z(), rec._p.x() - _center.x());
        double u = (phi + Math::_pi) / (2 * Math::_pi);
        double v = 0.5;

        Color normalMapColor = _normalMap->value(u, v, rec._p);
        Vec3 normalMapVec = Vec3(normalMapColor.r(), normalMapColor.g(), normalMapColor.b());
        Vec3 perturbedNormal = 2 * normalMapVec - Vec3(1, 1, 1);

        return perturbedNormal;
    }

    Aabb UnlimitedCylinder::boundingBox() const
    {
        Vec3 minPoint(_center.x() - _radius, _center.y() - Math::_infinity, _center.z() - _radius);
        Vec3 maxPoint(_center.x() + _radius, _center.y() + Math::_infinity, _center.z() + _radius);

        return Aabb(minPoint, maxPoint);
    }

    double UnlimitedCylinder::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        return 1.0 / (_radius * Math::_pi * 2);
    }

    Vec3 UnlimitedCylinder::random(const Point3 &origin) const
    {
        double theta = Math::randomDouble(0, 2 * Math::_pi);
        double y = Math::randomDouble(_center.y() - Math::_infinity, _center.y() + Math::_infinity);
        double x = _center.x() + _radius * cos(theta);
        double z = _center.z() + _radius * sin(theta);

        return Vec3(x, y, z) - origin;
    }

    std::shared_ptr<Hittable> UnlimitedCylinder::applyTransformation(const Matrix &matrix)
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
                _radius *= matrix._data[0][0];
                break;
            }

            case Matrix::Type::ShearX:
            case Matrix::Type::ShearY:
            case Matrix::Type::ShearZ: {
                break;
            }
        }
        return Factory::createHittable<UnlimitedCylinder>(_center, _radius, _mat);
    }
}
