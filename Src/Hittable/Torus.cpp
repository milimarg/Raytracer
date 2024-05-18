/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Torus
*/

#include "Torus.hpp"

namespace rtx
{
    Torus::Torus(const Point3 &center, double majorRadius, double minorRadius, std::shared_ptr<Material> mat) :
    _center(center), _majorRadius(majorRadius), _minorRadius(minorRadius), _mat(mat)
    {
    }

    // ! Be careful, this class does not represent exactly how a torus works
    bool Torus::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
		Vec3 oc = r.origin() - _center;
		double a = r.direction().lengthSquared();
		double b = 2.0 * Vec3::dot(r.direction(), oc);
		double c = oc.lengthSquared() - (pow(_majorRadius, 2) + pow(_minorRadius, 2));

		double discriminant = pow(b, 2) - 4 * a * c;
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
		if (hitPoint.z() < _center.z() - _minorRadius)
			hitPoint = Vec3(hitPoint.x(), hitPoint.y(), _center.z() - _minorRadius);
		if (hitPoint.z() > _center.z() + _minorRadius)
			hitPoint = Vec3(hitPoint.x(), hitPoint.y(), _center.z() + _minorRadius);
		Vec3 localHitPoint = hitPoint - _center;
		Vec3 u = Vec3(localHitPoint.x(), localHitPoint.y(), 0.0f);
		u = u.normalized() * _majorRadius;
		Vec3 torusPoint = u + _center;
		Vec3 outwardNormal = (hitPoint - torusPoint).normalized();

		double holeRadius = _majorRadius - _minorRadius;
		double distanceToAxis = sqrt(localHitPoint.x() * localHitPoint.x() + localHitPoint.y() * localHitPoint.y());
		if (distanceToAxis < holeRadius)
			return false;
        rec._t = t;
        rec._p = hitPoint;
        rec.setFaceNormal(r, outwardNormal);
        rec._mat = _mat;
        return true;
    }

    Aabb Torus::boundingBox() const
    {
        Vec3 minPoint(_center.x() - (_majorRadius + _minorRadius), _center.y() - _minorRadius - _majorRadius, _center.z() - (_majorRadius + _minorRadius));
        Vec3 maxPoint(_center.x() + (_majorRadius + _minorRadius), _center.y() + _minorRadius + _majorRadius, _center.z() + (_majorRadius + _minorRadius));

        return Aabb(minPoint, maxPoint);
    }

    double Torus::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        return 0.0;
    }

    Vec3 Torus::random(const Point3 &origin) const
    {
        return Vec3(1, 0, 0);
    }

    std::shared_ptr<Hittable> Torus::applyTransformation(const Matrix &matrix)
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
                _minorRadius *= matrix._data[0][0];
                _majorRadius *= matrix._data[1][1];
                break;
            }

            case Matrix::Type::ShearX:
            case Matrix::Type::ShearY:
            case Matrix::Type::ShearZ: {
                break;
            }
        }
        return Factory::createHittable<Torus>(_center, _minorRadius, _majorRadius, _mat);
    }
}
