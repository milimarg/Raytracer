/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Obj.hpp
*/

#ifndef B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_OBJ_HPP
    #define B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_OBJ_HPP
    #include <memory>
    #include "HittableList.hpp"
    #include "Triangle.hpp"

namespace rtx
{
    class Obj : public HittableList {
    public:
        Obj(const std::string &filepath, std::shared_ptr<Material> mat);
        ~Obj();
        void parse();
        std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix);
        Obj &operator*(const Matrix &matrix);

        std::vector<Triangle> _triangles;
    private:
        const std::string &_filepath;
        std::shared_ptr<Material> _mat;
    };
};

#endif //B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_OBJ_HPP
