/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Box.hpp
*/

#ifndef B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_BOX_HPP
    #define B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_BOX_HPP
    #include "Quad.hpp"
    #include <memory>

namespace rtx
{
    class Box : public HittableList {
    public:
        Box(
            const Point3 &a,
            const Point3 &b,
            std::shared_ptr<Material> mat,
            std::shared_ptr<Texture> normalMap = nullptr
        );
        ~Box();
        std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix);

    private:
        Point3 _a;
        Point3 _b;
        std::shared_ptr<Material> _mat;
    };
};

#endif //B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_BOX_HPP
