/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace rtx
{
    Sphere::Sphere(
        const Point3 &center,
        double radius,
        std::shared_ptr<Material> mat,
        std::shared_ptr<Texture> normalMap
    )
        : _center1(center),
        _radius(fmax(0,radius)),
        _mat(mat),
        _isMoving(false),
        _normalMap(normalMap)
    {
        auto rvec = Vec3(radius, radius, radius);
        _bbox = Aabb(_center1 - rvec, _center1 + rvec);
    }

    Sphere::Sphere(
        const Point3 &center1,
        const Point3 &center2,
        double radius,
        std::shared_ptr<Material> mat,
        std::shared_ptr<Texture> normalMap
    )
        : _center1(center1),
        _radius(fmax(0,radius)),
        _mat(mat),
        _isMoving(true),
        _normalMap(normalMap)
    {
        auto rvec = Vec3(radius, radius, radius);
        Aabb box1(center1 - rvec, center1 + rvec);
        Aabb box2(center2 - rvec, center2 + rvec);
        _bbox = Aabb(box1, box2);

        _centerVec = center2 - center1;
    }

    bool Sphere::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        Point3 center = _isMoving ? sphereCenter(r.time()) : _center1;
        Vec3 oc = center - r.origin();
        auto a = r.direction().lengthSquared();
        auto h = Vec3::dot(r.direction(), oc);
        auto c = oc.lengthSquared() - _radius * _radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = sqrt(discriminant);

        auto root = (h - sqrtd) / a;
        if (!rayT.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!rayT.surrounds(root))
                return false;
        }

        rec._t = root;
        rec._p = r.at(rec._t);
        Vec3 outwardNormal = (rec._p - center) / _radius;
        if (_normalMap)
           outwardNormal = getNormalFromMap(rec);
        rec.setFaceNormal(r, outwardNormal);
        getSphereUv(outwardNormal, rec._u, rec._v);

        rec._mat = _mat;

        return true;
    }

    Vec3 Sphere::getNormalFromMap(const HitRecord &rec) const
    {
        Vec3 pointOnSurface = rec._p - _center1;
        double phi = atan2(pointOnSurface.z(), pointOnSurface.x());
        double theta = asin(pointOnSurface.y() / _radius);
        double u = 1 - (phi + Math::_pi) / (2 * Math::_pi);
        double v = (theta + Math::_pi / 2) / Math::_pi;

        Color normalMapColor = _normalMap->value(u, v, rec._p);
        Vec3 normalMapVec = Vec3(normalMapColor.r(), normalMapColor.g(), normalMapColor.b());
        Vec3 perturbedNormal = 2 * normalMapVec - Vec3(1, 1, 1);

        return perturbedNormal;
    }

    Aabb Sphere::boundingBox() const
    {
        return _bbox;
    }

    double Sphere::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        HitRecord rec;
        if (!this->hit(Ray(origin, direction), Interval(0.001, Math::_infinity), rec))
            return 0;

        auto cosThetaMax = sqrt(1 - _radius * _radius / (_center1 - origin).lengthSquared());
        auto solidAngle = 2 * Math::_pi * (1 - cosThetaMax);

        return  1 / solidAngle;
    }

    Vec3 Sphere::random(const Point3 &origin) const
    {
        Vec3 direction = _center1 - origin;
        auto distanceSquared = direction.lengthSquared();
        Onb uvw;
        uvw.buildFromW(direction);
        return uvw.local(randomToSphere(_radius, distanceSquared));
    }

    Point3 Sphere::sphereCenter(double time) const
    {
        return _center1 + time * _centerVec;
    }

    void Sphere::getSphereUv(const Point3 &p, double &u, double &v)
    {
        auto theta = acos(-p.y());
        auto phi = atan2(-p.z(), p.x()) + Math::_pi;

        u = phi / (2*Math::_pi);
        v = theta / Math::_pi;
    }

    Vec3 Sphere::randomToSphere(double radius, double distanceSquared)
    {
        auto r1 = Math::randomDouble();
        auto r2 = Math::randomDouble();
        auto z = 1 + r2 * (sqrt(1 - radius * radius / distanceSquared) - 1);

        auto phi = 2 * Math::_pi * r1;
        auto x = cos(phi) * sqrt(1 - z * z);
        auto y = sin(phi) * sqrt(1 - z * z);

        return Vec3(x, y, z);
    }

    std::shared_ptr<Hittable> Sphere::applyTransformation(const Matrix &matrix)
    {
        switch (matrix.getType()) {
            case Matrix::Type::Translation: {
                _center1 = _center1 * matrix;
                Vec3 offset(matrix._data[3][0], matrix._data[3][1], matrix._data[3][2]);
                _bbox = _bbox + offset;
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
        return make_shared<Sphere>(_center1, _radius, _mat);
    }
};
