/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Triangle.hpp
*/

#ifndef B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_TRIANGLE_HPP
    #define B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_TRIANGLE_HPP
    #include <array>
    #include "Vec3.hpp"
    #include "Hittable.hpp"

namespace rtx
{
    class Triangle : public Hittable {
    public:
        Triangle();
        Triangle(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, std::shared_ptr<Material> mat);
        Triangle(const Triangle &triangle, std::shared_ptr<Material> mat);

        bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
        Aabb boundingBox() const override;
        void setBoundingBox();
        double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
        Vec3 random(const Point3 &origin) const override;
        std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override;
        std::ostream &operator<<(std::ostream &s);
        Triangle operator*(const Matrix &matrix);
        Triangle &operator*=(const Matrix &matrix);

        std::array<Vec3, 3> p;
    private:
        Vec3 _edge1;
        Vec3 _edge2;
        Vec3 _normal;
        double _area;
        std::shared_ptr<Material> _mat;
        Aabb _bbox;
    };
};

#endif //B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_TRIANGLE_HPP
