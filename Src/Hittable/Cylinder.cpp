/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-rtracer-florent.guittre
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include "Onb.hpp"

namespace rtx
{
    Cylinder::Cylinder(
        const Point3 &center,
        double radius,
        double height,
        std::shared_ptr<Material> mat,
        std::shared_ptr<Texture> normalMap
    ) : _center(center),
    _radius(radius),
    _height(height),
    _mat(mat),
    _normalMap(normalMap)
    {
    }

    bool Cylinder::checkBotAndTop(const Ray &r, HitRecord &rec, double t) const
    {
        Vec3 center = Vec3(_center.x(), _center.y() + _height, _center.z());
        double top = (center.y() - r.origin().y()) / r.direction().y();
        double bot = (_center.y() - r.origin().y()) / r.direction().y();
        if (top <= 0 || bot <= 0)
            return false;

        Vec3 hitPointTop = r.origin() + r.direction() * top;
        double distTop = Vec3::distance(hitPointTop, center);

        Vec3 hitPointBot = r.origin() + r.direction() * bot;
        double distBot = Vec3::distance(hitPointBot, _center);

        if (distTop <= _radius) {
            Vec3 origin = r.origin();
            double dist1 = Vec3::distance(origin, hitPointTop);
            double dist2 = Vec3::distance(origin, hitPointBot);
            if (dist1 < dist2 || distBot >= _radius) {
                rec._t = t;
                rec._p = hitPointTop;
                rec.setFaceNormal(r, hitPointTop.normalized());
                if (_normalMap)
                    rec.setFaceNormal(r, getNormalFromMap(rec));
                rec._mat = _mat;
                return true;
            }
        }

        if (distBot <= _radius) {
            rec._t = t;
            rec._p = hitPointBot;
            rec.setFaceNormal(r, hitPointBot.normalized());
            if (_normalMap)
                rec.setFaceNormal(r, getNormalFromMap(rec));
            rec._mat = _mat;
            return true;
        }
        return false;
    }

    bool Cylinder::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        Vec3 oc = r.origin() - _center;
        double a = pow(r.direction().x(), 2) + pow(r.direction().z(), 2);
        double b = 2 * (oc.x() * r.direction().x() + oc.z() * r.direction().z());
        double c = pow(oc.x(), 2) + pow(oc.z(), 2) - pow(_radius, 2);

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
        if (hitPoint.y() >= _center.y() && hitPoint.y() <= _center.y() + _height) {
            rec._t = t;
            rec._p = r.at(t);
            rec.setFaceNormal(r, hitPoint.normalized());
            if (_normalMap)
                rec.setFaceNormal(r, getNormalFromMap(rec));
            rec._mat = _mat;
            return true;
        }
        if (r.direction().y() == 0)
            return false;
        return checkBotAndTop(r, rec, t);
    }

    Vec3 Cylinder::getNormalFromMap(const HitRecord &rec) const
    {
        double phi = atan2(rec._p.z() - _center.z(), rec._p.x() - _center.x());
        double u = (phi + Math::_pi) / (2 * Math::_pi);
        double v = (rec._p.y() - _center.y()) / _height;

        Color normalMapColor = _normalMap->value(u, v, rec._p);
        Vec3 normalMapVec = Vec3(normalMapColor.r(), normalMapColor.g(), normalMapColor.b());
        Vec3 perturbedNormal = 2 * normalMapVec - Vec3(1, 1, 1);

        return perturbedNormal;
    }

    Aabb Cylinder::boundingBox() const
    {
        Vec3 minPoint(_center.x() - _radius, _center.y(), _center.z() - _radius);
        Vec3 maxPoint(_center.x() + _radius, _center.y() + _height, _center.z() + _radius);

        return Aabb(minPoint, maxPoint);
    }

    double Cylinder::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        HitRecord rec;
        if (!this->hit(Ray(origin, direction), Interval(0.001, Math::_infinity), rec))
            return 0.0;

        double cosThetaMax = sqrt(1 - _radius * _radius / (_center - origin).lengthSquared());
        double solidAngle = 2 * Math::_pi * (1 - cosThetaMax);

        return 1.0 / solidAngle;
    }

    Vec3 Cylinder::random(const Point3 &origin) const
    {
        Vec3 direction = _center - origin;
        double distanceSquared = direction.lengthSquared();
        Onb uvw;
        uvw.buildFromW(direction);
        double rand1 = Math::randomDouble();
        double rand2 = Math::randomDouble();
        double phi = 2 * Math::_pi * rand1;
        double h = _center.y() - origin.y() + _height * rand2;
        double x = _center.x() + _radius * cos(phi);
        double y = origin.y() + h;
        double z = _center.z() + _radius * sin(phi);

        return Vec3(x, y, z);
    }

    std::shared_ptr<Hittable> Cylinder::applyTransformation(const Matrix &matrix)
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
                _height *= matrix._data[1][1];
                break;
            }

            case Matrix::Type::ShearX:
            case Matrix::Type::ShearY:
            case Matrix::Type::ShearZ: {
                break;
            }
        }
        return Factory::createHittable<Cylinder>(_center, _radius, _height, _mat);
    }
}
