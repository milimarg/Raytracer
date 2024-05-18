/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** matrix.cpp
*/

#include "Math/Matrix/Matrix.hpp"
#include "Vec3.hpp"
#include <cmath>

namespace rtx
{
    Matrix::Matrix() {}

    Matrix::~Matrix() {}

    void Matrix::clear()
    {
        for (size_t i = 0; i < 4; i += 1)
            for (size_t j = 0; j < 4; j += 1)
                _data[i][j] = 0;
    }

    // https://en.wikipedia.org/wiki/Identity_matrix (first paragraph)
    void Matrix::applyIdentity()
    {
        for (size_t i = 0; i < 4; i += 1)
            _data[i][i] = 1.0f;
    }

    // https://wikimedia.org/api/rest_v1/media/math/render/svg/f8291f8c9e148126f931b49fa4fa9a96827aceeb
    // Cf. https://en.wikipedia.org/wiki/Translation_(geometry)
    void Matrix::applyTranslation(const Vec3 &v)
    {
        applyIdentity();
        _data[3][0] = v.x();
        _data[3][1] = v.y();
        _data[3][2] = v.z();
        _type = Type::Translation;
    }

    // https://wikimedia.org/api/rest_v1/media/math/render/svg/a6821937d5031de282a190f75312353c970aa2df
    // Cf. https://en.wikipedia.org/wiki/Rotation_matrix
    void Matrix::applyRotationX(const float angle)
    {
        applyIdentity();
        const float radians = Math::degreesToRadians(angle);
        _data[1][1] = cosf(radians);
        _data[1][2] = sinf(radians);
        _data[2][1] = -sinf(radians);
        _data[2][2] = cosf(radians);
        _type = Type::RotationX;
    }

    void Matrix::applyRotationY(const float angle)
    {
        applyIdentity();
        const float radians = Math::degreesToRadians(angle);
        _data[0][0] = cosf(radians);
        _data[0][2] = -sinf(radians);
        _data[2][0] = sinf(radians);
        _data[2][2] = cosf(radians);
        _type = Type::RotationY;
    }

    void Matrix::applyRotationZ(const float angle)
    {
        applyIdentity();
        const float radians = Math::degreesToRadians(angle);
        _data[0][0] = cosf(radians);
        _data[0][1] = sinf(radians);
        _data[1][0] = -sinf(radians);
        _data[1][1] = cosf(radians);
        _type = Type::RotationZ;
    }

    // https://wikimedia.org/api/rest_v1/media/math/render/svg/4d4561ec79e4ad2fb898cf7b2f4ec0873a01fb31
    // Cf. https://en.wikipedia.org/wiki/Scaling_(geometry)#Matrix
    void Matrix::applyScale(const Vec3 &v)
    {
        applyIdentity();
        _data[0][0] = v.x();
        _data[1][1] = v.y();
        _data[2][2] = v.z();
        _type = Type::Scale;
    }

    void Matrix::applyScale(const float radius)
    {
        applyScale(rtx::Vec3(radius, radius, radius));
        _type = Type::Scale;
    }

    // https://www.geeksforgeeks.org/computer-graphics-3d-shearing-transformation/
    void Matrix::applyShearX(const float y, const float z)
    {
        applyIdentity();
        _data[0][1] = y;
        _data[0][2] = z;
        _type = Type::ShearX;
    }

    void Matrix::applyShearY(const float x, const float z)
    {
        applyIdentity();
        _data[1][0] = x;
        _data[1][2] = z;
        _type = Type::ShearY;
    }

    void Matrix::applyShearZ(const float x, const float y)
    {
        applyIdentity();
        _data[2][0] = x;
        _data[2][1] = y;
        _type = Type::ShearZ;
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &m)
    {
        for (int i = 0; i < 4; i += 1) {
            for (int j = 0; j < 4; j += 1) {
                out << m._data[i][j];
                if (j != 3)
                    out << ",\t";
            }
            out << std::endl;
        }
        return out;
    }
};
