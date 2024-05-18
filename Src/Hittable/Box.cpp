/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Box.cpp
*/

#include "Box.hpp"

namespace rtx
{
    Box::Box(
        const Point3 &a,
        const Point3 &b,
        std::shared_ptr<Material> mat,
        std::shared_ptr<Texture> normalMap
    )
        : _a(a), _b(b), _mat(mat) {
        Point3 min(fmin(a.x(), b.x()), fmin(a.y(), b.y()), fmin(a.z(), b.z()));
        Point3 max(fmax(a.x(), b.x()), fmax(a.y(), b.y()), fmax(a.z(), b.z()));

        Vec3 dx(max.x() - min.x(), 0, 0);
        Vec3 dy(0, max.y() - min.y(), 0);
        Vec3 dz(0, 0, max.z() - min.z());

        add(Factory::createHittable<Quad>(Point3(min.x(), min.y(), max.z()),  dx,  dy, mat, normalMap)); // front
        add(Factory::createHittable<Quad>(Point3(max.x(), min.y(), max.z()), -dz,  dy, mat, normalMap)); // right
        add(Factory::createHittable<Quad>(Point3(max.x(), min.y(), min.z()), -dx,  dy, mat, normalMap)); // back
        add(Factory::createHittable<Quad>(Point3(min.x(), min.y(), min.z()),  dz,  dy, mat, normalMap)); // left
        add(Factory::createHittable<Quad>(Point3(min.x(), max.y(), max.z()),  dx, -dz, mat, normalMap)); // top
        add(Factory::createHittable<Quad>(Point3(min.x(), min.y(), min.z()),  dx,  dz, mat, normalMap)); // bottom
    }

    Box::~Box() {}

    std::shared_ptr<Hittable> Box::applyTransformation(const Matrix &matrix)
    {
        switch (matrix.getType()) {
            case Matrix::Type::Translation:
            case Matrix::Type::RotationX:
            case Matrix::Type::RotationY:
            case Matrix::Type::RotationZ: {
                _a = _a * matrix;
                _b = _b * matrix;
                break;
            }
            case Matrix::Type::Scale:
                _b = _b * matrix;
                break;
            case Matrix::Type::ShearX:
            case Matrix::Type::ShearY:
            case Matrix::Type::ShearZ:
                break;
        }
        return Factory::createHittable<Box>(_a, _b, _mat);
    }
};
