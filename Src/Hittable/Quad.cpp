/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Quad
*/

#include "Quad.hpp"

namespace rtx
{
    Quad::Quad(
        const Point3 &Q,
        const Vec3 &u,
        const Vec3 &v,
        std::shared_ptr<Material> mat,
        std::shared_ptr<Texture> normalMap)
        : _Q(Q),
        _u(u),
        _v(v),
        _mat(mat),
        _normalMap(normalMap)
    {
        auto n = Vec3::cross(u, v);
        _normal = Vec3::unitVector(n);
        _D = Vec3::dot(_normal, Q);
        _w = n / Vec3::dot(n, n);

        _area = n.length();

        setBoundingBox();
    }

    void Quad::setBoundingBox()
    {
        auto bboxDiagonal1 = Aabb(_Q, _Q + _u + _v);
        auto bboxDiagonal2 = Aabb(_Q + _u, _Q + _v);
        _bbox = Aabb(bboxDiagonal1, bboxDiagonal2);
    }

    bool Quad::isInterior(double a, double b, HitRecord &rec) const
    {
        Interval unitInterval = Interval(0, 1);

        if (!unitInterval.contains(a) || !unitInterval.contains(b))
            return false;

        rec._u = a;
        rec._v = b;
        return true;
    }

    Aabb Quad::boundingBox() const
    {
        return _bbox;
    }

    bool Quad::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        auto denom = Vec3::dot(_normal, r.direction());

        if (fabs(denom) < 1e-8)
            return false;

        auto t = (_D - Vec3::dot(_normal, r.origin())) / denom;
        if (!rayT.contains(t))
            return false;

        auto intersection = r.at(t);
        Vec3 planarHitptVector = intersection - _Q;
        auto alpha = Vec3::dot(_w, Vec3::cross(planarHitptVector, _v));
        auto beta = Vec3::dot(_w, Vec3::cross(_u, planarHitptVector));

        if (!isInterior(alpha, beta, rec))
            return false;

        rec._t = t;
        rec._p = intersection;
        rec._mat = _mat;

        if (_normalMap)
            rec.setFaceNormal(r, getNormalFromMap(rec));
        else
            rec.setFaceNormal(r, _normal);

        return true;
    }

    Vec3 Quad::getNormalFromMap(const HitRecord &rec) const
    {
        Color normalMapColor = _normalMap->value(rec._u, rec._v, rec._p);
        Vec3 normalMapVec = Vec3(normalMapColor.r(), normalMapColor.g(), normalMapColor.b());
        Vec3 perturbedNormal = 2 * normalMapVec - Vec3(1, 1, 1);
        return perturbedNormal;
    }

    double Quad::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        HitRecord rec;
        if (!this->hit(Ray(origin, direction), Interval(0.001, Math::_infinity), rec))
            return 0;

        auto distance_squared = rec._t * rec._t * direction.lengthSquared();
        auto cosine = fabs(Vec3::dot(direction, rec._normal) / direction.length());

        return distance_squared / (cosine * _area);
    }

    Vec3 Quad::random(const Point3 &origin) const
    {
        auto p = _Q + (Math::randomDouble() * _u) + (Math::randomDouble() * _v);
        return p - origin;
    }

    std::shared_ptr<Hittable> Quad::applyTransformation(const Matrix &matrix)
    {
        switch (matrix.getType()) {
            case Matrix::Type::Translation: {
                _Q = _Q * matrix;
                Vec3 offset(matrix._data[3][0], matrix._data[3][1], matrix._data[3][2]);
                _bbox = _bbox + offset;
                break;
            }

            case Matrix::Type::RotationX:
            case Matrix::Type::RotationY:
            case Matrix::Type::RotationZ: {
                _Q = _Q * matrix;
                _u = _u * matrix;
                _v = _v * matrix;
                _w = _w * matrix;

                double radians = Math::degreesToRadians(std::acos(matrix._data[0][0]));
                float sinTheta = sin(radians);
                float cosTheta = cos(radians);

                Point3 min( Math::_infinity,  Math::_infinity,  Math::_infinity);
                Point3 max(-Math::_infinity, -Math::_infinity, -Math::_infinity);

                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        for (int k = 0; k < 2; k++) {
                            auto x = i * _bbox._x._max + (1 - i) * _bbox._x._min;
                            auto y = j * _bbox._y._max + (1 - j) * _bbox._y._min;
                            auto z = k * _bbox._z._max + (1 - k) * _bbox._z._min;

                            auto newx = cosTheta * x + sinTheta * z;
                            auto newz = -sinTheta * x + cosTheta * z;

                            Vec3 tester(newx, y, newz);

                            for (int c = 0; c < 3; c++) {
                                min[c] = fmin(min[c], tester[c]);
                                max[c] = fmax(max[c], tester[c]);
                            }
                        }
                    }
                }
                _bbox = Aabb(min, max);
                break;
            }

            case Matrix::Type::Scale: {
                double x = matrix._data[0][0];
                double y = matrix._data[1][1];
                double z = matrix._data[2][2];
                Vec3 originalU = _u;
                Vec3 originalV = _v;
                Vec3 originalW = _w;

                _u = _u * x;
                _v = _v * y;
                _w = _w * z;

                float newOriginX = _Q.x() + (originalU.x() - _u.x()) / 2;
                float newOriginY = _Q.y() + (originalV.y() - _v.y()) / 2;
                float newOriginZ = _Q.z() + (originalW.z() - _w.z()) / 2;
                _Q = rtx::Vec3(newOriginX, newOriginY, _Q.z());
                break;
            }

            case Matrix::Type::ShearX:
            case Matrix::Type::ShearY:
            case Matrix::Type::ShearZ: {
                break;
            }
        }
        return Factory::createHittable<Quad>(_Q, _u, _v, _mat);
    }
};
