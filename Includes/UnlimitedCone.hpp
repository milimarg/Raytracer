/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** UnlimitedCone
*/

#ifndef UNLIMITEDCONE_HPP_
    #define UNLIMITEDCONE_HPP_
    #include "Hittable.hpp"
    #include "Texture.hpp"

namespace rtx
{
    class UnlimitedCone : public Hittable {
        public:
            UnlimitedCone(
                const Point3 &center,
                std::shared_ptr<Material> mat,
                std::shared_ptr<Texture> normalMap = nullptr
            );

            bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
            Aabb boundingBox() const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override;

        private:
            Point3 _center;
            std::shared_ptr<Material> _mat;
            Aabb _bbox;
            std::shared_ptr<Texture> _normalMap;

            Vec3 getNormalFromMap(const HitRecord &rec) const;
    };
};

#endif /* !UNLIMITEDCONE_HPP_ */
