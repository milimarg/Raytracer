/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** RotateY
*/

#include "RotateY.hpp"

namespace rtx
{
    RotateY::RotateY(std::shared_ptr<Hittable> object, double angle)
        : _object(object)
    {
        auto radians = Math::degreesToRadians(angle);
        _sinTheta = sin(radians);
        _cosTheta = cos(radians);
        _bbox = object->boundingBox();

        Point3 min( Math::_infinity,  Math::_infinity,  Math::_infinity);
        Point3 max(-Math::_infinity, -Math::_infinity, -Math::_infinity);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    auto x = i * _bbox._x._max + (1 - i) * _bbox._x._min;
                    auto y = j * _bbox._y._max + (1 - j) * _bbox._y._min;
                    auto z = k * _bbox._z._max + (1 - k) * _bbox._z._min;

                    auto newx =  _cosTheta * x + _sinTheta * z;
                    auto newz = -_sinTheta * x + _cosTheta * z;

                    Vec3 tester(newx, y, newz);

                    for (int c = 0; c < 3; c++) {
                        min[c] = fmin(min[c], tester[c]);
                        max[c] = fmax(max[c], tester[c]);
                    }
                }
            }
        }

        _bbox = Aabb(min, max);
    }

    bool RotateY::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        auto origin = r.origin();
        auto direction = r.direction();

        origin[0] = _cosTheta * r.origin()[0] - _sinTheta * r.origin()[2];
        origin[2] = _sinTheta * r.origin()[0] + _cosTheta * r.origin()[2];

        direction[0] = _cosTheta * r.direction()[0] - _sinTheta * r.direction()[2];
        direction[2] = _sinTheta * r.direction()[0] + _cosTheta * r.direction()[2];

        Ray rotated_r(origin, direction, r.time());

        if (!_object->hit(rotated_r, rayT, rec))
            return false;

        auto p = rec._p;
        p[0] =  _cosTheta * rec._p[0] + _sinTheta * rec._p[2];
        p[2] = -_sinTheta * rec._p[0] + _cosTheta * rec._p[2];

        auto normal = rec._normal;
        normal[0] =  _cosTheta * rec._normal[0] + _sinTheta * rec._normal[2];
        normal[2] = -_sinTheta * rec._normal[0] + _cosTheta * rec._normal[2];

        rec._p = p;
        rec._normal = normal;

        return true;
    }

    Aabb RotateY::boundingBox() const
    {
        return _bbox;
    }

    double RotateY::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        return _object->pdfValue(rotate(origin), rotate(direction));
    }

    Vec3 RotateY::random(const Point3 &origin) const
    {
        return _object->random(rotate(origin));
    }

    Point3 RotateY::rotate(const Point3 &p) const
    {
        double x =  _cosTheta * p.x() + _sinTheta * p.z();
        double z = -_sinTheta * p.x() + _cosTheta * p.z();
        return Point3(x, p.y(), z);
    }
};
