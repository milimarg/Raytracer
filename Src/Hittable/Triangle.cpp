/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Triangle.cpp
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Sphere.hpp"
#include "Quad.hpp"
#include "Scene.hpp"
#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "DiffuseLight.hpp"
#include "Metal.hpp"
#include "Isotropic.hpp"
#include "../../Includes/Triangle.hpp"

namespace rtx
{
    Triangle::Triangle() {}

    Triangle::Triangle(const rtx::Vec3 &A, const rtx::Vec3 &B, const rtx::Vec3 &C, std::shared_ptr<Material> mat)
        : _mat(mat)
    {
        p[0] = A;
        p[1] = B;
        p[2] = C;
        _edge1 = B - A;
        _edge2 = C - A;
        _normal = Vec3::unitVector(Vec3::cross(_edge1, _edge2));
        _area = 0.5 * Vec3::cross(_edge1, _edge2).length();
        setBoundingBox();
    }

    Triangle::Triangle(const rtx::Triangle &triangle, std::shared_ptr<Material> mat)
        : Triangle(triangle.p[0], triangle.p[1], triangle.p[2], mat)
    {}

    bool Triangle::hit(const rtx::Ray &r, rtx::Interval rayT, rtx::HitRecord &rec) const
    {
        auto h = Vec3::cross(r.direction(), _edge2);
        auto a = Vec3::dot(_edge1, h);

        if (fabs(a) < 1e-8)
            return false;

        auto f = 1 / a;
        auto s = r.origin() - p[0];
        auto u = f * Vec3::dot(s, h);

        if (u < 0.0 || u > 1.0)
            return false;

        auto q = Vec3::cross(s, _edge1);
        auto v = f * Vec3::dot(r.direction(), q);

        if (v < 0.0 || u + v > 1.0)
            return false;

        auto t = f * Vec3::dot(_edge2, q);

        if (!rayT.contains(t))
            return false;

        rec._t = t;
        rec._p = r.at(t);
        rec._mat = _mat;
        rec.setFaceNormal(r, _normal);

        return true;
    }

    Aabb Triangle::boundingBox() const
    {
        return _bbox;
    }

    void Triangle::setBoundingBox()
    {
        auto min_point = Point3(
                fmin(p[0].x(), fmin(p[1].x(), p[2].x())),
                fmin(p[0].y(), fmin(p[1].y(), p[2].y())),
                fmin(p[0].z(), fmin(p[1].z(), p[2].z()))
        );

        auto max_point = Point3(
                fmax(p[0].x(), fmax(p[1].x(), p[2].x())),
                fmax(p[0].y(), fmax(p[1].y(), p[2].y())),
                fmax(p[0].z(), fmax(p[1].z(), p[2].z()))
        );

        _bbox = Aabb(min_point, max_point);
    }

    double Triangle::pdfValue(const rtx::Point3 &origin, const rtx::Vec3 &direction) const
    {
        HitRecord rec;
        if (!this->hit(Ray(origin, direction), Interval(0.001, Math::_infinity), rec))
            return 0;

        auto distance_squared = rec._t * rec._t * direction.lengthSquared();
        auto cosine = fabs(Vec3::dot(direction, rec._normal) / direction.length());

        return distance_squared / (cosine * _area);
    }

    Vec3 Triangle::random(const rtx::Point3 &origin) const
    {
        float r1 = Math::randomDouble();
        float r2 = Math::randomDouble();

        float sqrt_r1 = sqrt(r1);

        return (1 - sqrt_r1) * p[0] + (sqrt_r1 * (1 - r2)) * p[1] + (sqrt_r1 * r2) * p[2] - origin;
    }

    std::shared_ptr<Hittable> Triangle::applyTransformation(const rtx::Matrix &matrix)
    {
        Triangle newTriangle(
                p[0] * matrix,
                p[1] * matrix,
                p[2] * matrix,
                _mat
                );

        return std::make_shared<Triangle>(newTriangle, _mat);
    }

    std::ostream &Triangle::operator<<(std::ostream &s)
    {
        return s << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
    }

    Triangle Triangle::operator*(const rtx::Matrix &matrix)
    {
        return Triangle(
                p[0] * matrix,
                p[1] * matrix,
                p[2] * matrix,
                _mat
                );
    }

    Triangle &Triangle::operator*=(const rtx::Matrix &matrix)
    {
        p[0] * matrix;
        p[1] * matrix;
        p[2] * matrix;
        return *this;
    }
};
