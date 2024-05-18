/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** matrix.hpp
*/

#ifndef B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_MATRIX_HPP
    #define B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_MATRIX_HPP
    #include <ostream>

namespace rtx
{
    class Vec3;

    class Matrix {
    public:
        enum class Type {
            Translation,
            RotationX,
            RotationY,
            RotationZ,
            Scale,
            ShearX,
            ShearY,
            ShearZ
        };

        Matrix();
        ~Matrix();

        Type getType() const { return _type; }

        void clear();
        void applyIdentity();

        void applyTranslation(const Vec3 &v);

        void applyRotationX(const float angle);
        void applyRotationY(const float angle);
        void applyRotationZ(const float angle);

        void applyScale(const Vec3 &v);
        void applyScale(const float radius);

        void applyShearX(const float y, const float z);
        void applyShearY(const float x, const float z);
        void applyShearZ(const float x, const float y);

        float _data[4][4] = {0};

        private:
            Type _type;
    };

    std::ostream &operator<<(std::ostream &stream, const rtx::Matrix &m);
};

#endif //B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_MATRIX_HPP
