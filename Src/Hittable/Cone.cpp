/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-rtracer-florent.guittre
** File description:
** Cone
*/

#include "Cone.hpp"
#include "Onb.hpp"

namespace rtx
{
    Cone::Cone(
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
        _center = Vec3(center.x(), center.y() + height, center.z());
        _base = center;
    }

    bool Cone::checkBot(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        Vec3 oc = r.origin() - _base;
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
        if (hitPoint.y() >= _base.y() && hitPoint.y() <= _base.y() + _height)
            return false;
        if (r.direction().y() == 0)
            return false;

        double top = (_base.y() + _height - r.origin().y()) / r.direction().y();
        double bot = (_base.y() - r.origin().y()) / r.direction().y();

        if (top <= 0 || bot <= 0)
            return false;

        Vec3 hitPointTop = r.origin() + r.direction() * top;
        double distTop = Vec3::distance(hitPointTop, _base);

        Vec3 hitPointBot = r.origin() + r.direction() * bot;
        double distBot = Vec3::distance(hitPointBot, _base);

        if (distTop <= _radius) {
            Vec3 origin = r.origin();
            double dist1 = Vec3::distance(origin, hitPointTop);
            double dist2 = Vec3::distance(origin, hitPointBot);
            if (dist1 < dist2 || !((distBot < _radius) || distBot == _radius))
                return false;
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

    bool Cone::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        Vec3 oc = r.origin() - _center;
        double k = pow((_radius / _height), 2);

        double a = pow(r.direction().x(), 2)  - k * pow(r.direction().y(), 2) + pow(r.direction().z(), 2);
        double b = 2 * (r.direction().x() * oc.x()  - k * r.direction().y() * oc.y() + r.direction().z() * oc.z());
        double c = pow(oc.x(), 2) - k * pow(oc.y(), 2) + pow(oc.z(), 2);
        double discriminant = pow(b, 2) - 4 * a * c;

        if (discriminant < 0)
            return checkBot(r, rayT, rec);;

        double t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (!rayT.surrounds(t)) {
            t = (-b + sqrt(discriminant)) / (2.0 * a);
            if (!rayT.surrounds(t))
                return checkBot(r, rayT, rec);;
        }
        if (t < 0)
            return checkBot(r, rayT, rec);;
        double y = r.origin().y() + t * r.direction().y();
        if (y <= _center.y() && y >= _center.y() - _height) {
            Vec3 hitPoint = r.at(t);
            rec._t = t;
            rec._p = hitPoint;
            rec.setFaceNormal(r, hitPoint.normalized());
            if (_normalMap)
                rec.setFaceNormal(r, getNormalFromMap(rec));
            rec._mat = _mat;
            return true;
        }
        return checkBot(r, rayT, rec);
    }

    Vec3 Cone::getNormalFromMap(const HitRecord &rec) const
    {
        double phi = atan2(rec._p.z() - _base.z(), rec._p.x() - _base.x());
        double u = (phi + Math::_pi) / (2 * Math::_pi);
        double v = (rec._p.y() - _base.y()) / _height;

        Color normalMapColor = _normalMap->value(u, v, rec._p);
        Vec3 normalMapVec = Vec3(normalMapColor.r(), normalMapColor.g(), normalMapColor.b());
        Vec3 perturbedNormal = 2 * normalMapVec - Vec3(1, 1, 1);

        return perturbedNormal;
    }

    Aabb Cone::boundingBox() const
    {
        Vec3 minPoint(_center.x() - _radius, _center.y() - _height, _center.z() - _radius);
        Vec3 maxPoint(_center.x() + _radius, _center.y(), _center.z() + _radius);

        return Aabb(minPoint, maxPoint);
    }

    double Cone::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        HitRecord rec;
        if (!this->hit(Ray(origin, direction), Interval(0.001, Math::_infinity), rec))
            return 0;

        auto distanceSquared = rec._t * rec._t * direction.lengthSquared();
        auto cosine = fabs(Vec3::dot(direction, rec._normal) / direction.length());
        auto area = Math::_pi * _radius * (_radius + sqrt(_radius * _radius + _height * _height));

        return distanceSquared / (cosine * area);
    }

    Vec3 Cone::random(const Point3 &origin) const
    {
        auto phi = 2 * Math::_pi * Math::randomDouble();
        auto h = Math::randomDouble() * _height;
        auto radius = h * _radius / _height;
        Vec3 p(radius * cos(phi), h, radius * sin(phi));

        Vec3 v = _center - origin;
        Onb uvw;
        uvw.buildFromW(v);
        return uvw.local(p);
    }


    std::shared_ptr<Hittable> Cone::applyTransformation(const Matrix &matrix)
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
        return Factory::createHittable<Cone>(_center, _radius, _height, _mat);
    }
}
