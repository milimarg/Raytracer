/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** HitRecord
*/

#include "HitRecord.hpp"

namespace rtx
{
    void HitRecord::setFaceNormal(const Ray &r, const Vec3 &outwardNormal)
    {
        _frontFace = Vec3::dot(r.direction(), outwardNormal) < 0;
        _normal = _frontFace ? outwardNormal : -outwardNormal;
    }
};
