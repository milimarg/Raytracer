/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Onb
*/

#include "Onb.hpp"

namespace rtx
{
    Vec3 Onb::operator[](int i) const
    {
        return _axis[i];
    }

    Vec3 &Onb::operator[](int i)
    {
        return _axis[i];
    }

    Vec3 Onb::u() const
    {
        return _axis[0];
    }

    Vec3 Onb::v() const
    {
        return _axis[1];
    }

    Vec3 Onb::w() const
    {
        return _axis[2];
    }

    Vec3 Onb::local(double a, double b, double c) const
    {
        return a * u() + b * v() + c * w();
    }

    Vec3 Onb::local(const Vec3 &a) const
    {
        return a.x() * u() + a.y() * v() + a.z() * w();
    }

    void Onb::buildFromW(const Vec3 &w)
    {
        Vec3 unit_w = Vec3::unitVector(w);
        Vec3 a = (fabs(unit_w.x()) > 0.9) ? Vec3(0,1,0) : Vec3(1,0,0);
        Vec3 v = Vec3::unitVector(Vec3::cross(unit_w, a));
        Vec3 u = Vec3::cross(unit_w, v);
        _axis[0] = u;
        _axis[1] = v;
        _axis[2] = unit_w;
    }
};
