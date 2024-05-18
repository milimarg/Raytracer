/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Aabb.cpp
*/

#include "Aabb.hpp"

namespace rtx
{
    const Aabb Aabb::_empty = Aabb(Interval::_empty, Interval::_empty, Interval::_empty);
    const Aabb Aabb::_universe = Aabb(Interval::_universe, Interval::_universe, Interval::_universe);

    Aabb operator+(const Aabb &bbox, const Vec3 &offset)
    {
        return Aabb(bbox._x + offset.x(), bbox._y + offset.y(), bbox._z + offset.z());
    }

    Aabb operator+(const Vec3 &offset, const Aabb &bbox)
    {
        return bbox + offset;
    }

    Aabb::Aabb(const Interval &x, const Interval &y, const Interval &z)
        : _x(x), _y(y), _z(z)
    {
        padToMinimums();
    }

    Aabb::Aabb(const Point3 &a, const Point3 &b)
    {
        _x = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
        _y = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
        _z = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);
        padToMinimums();
    }

    Aabb::Aabb(const Aabb &box0, const Aabb &box1)
    {
        _x = Interval(box0._x, box1._x);
        _y = Interval(box0._y, box1._y);
        _z = Interval(box0._z, box1._z);
    }

    const Interval &Aabb::axisInterval(int n) const
    {
        if (n == 1)
            return _y;
        if (n == 2)
            return _z;
        return _x;
    }

    bool Aabb::hit(const Ray &r, Interval ray_t) const
    {
        const Point3 &ray_orig = r.origin();
        const Vec3 & ray_dir  = r.direction();

        for (int axis = 0; axis < 3; axis++) {
            const Interval &ax = axisInterval(axis);
            const double adinv = 1.0 / ray_dir[axis];

            auto t0 = (ax._min - ray_orig[axis]) * adinv;
            auto t1 = (ax._max - ray_orig[axis]) * adinv;

            if (t0 < t1) {
                if (t0 > ray_t._min) ray_t._min = t0;
                if (t1 < ray_t._max) ray_t._max = t1;
            } else {
                if (t1 > ray_t._min) ray_t._min = t1;
                if (t0 < ray_t._max) ray_t._max = t0;
            }

            if (ray_t._max <= ray_t._min)
                return false;
        }
        return true;
    }

    int Aabb::longestAxis()
    {
        if (_x.size() > _y.size())
            return _x.size() > _z.size() ? 0 : 2;
        else
            return _y.size() > _z.size() ? 1 : 2;
    }

    void Aabb::padToMinimums()
    {
        double delta = 0.0001;
        if (_x.size() < delta) _x = _x.expand(delta);
        if (_y.size() < delta) _y = _y.expand(delta);
        if (_z.size() < delta) _z = _z.expand(delta);
    }
};
