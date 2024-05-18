/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** ConstantMedium
*/

#ifndef CONSTANTMEDIUM_HPP_
    #define CONSTANTMEDIUM_HPP_
    #include "Hittable.hpp"
    #include "Material.hpp"
    #include "Texture.hpp"
    #include "Isotropic.hpp"

namespace rtx
{
    class ConstantMedium : public Hittable {
        public:
            ConstantMedium(std::shared_ptr<Hittable> boundary, double density, std::shared_ptr<Texture> tex);
            ConstantMedium(std::shared_ptr<Hittable> boundary, double density, const Color &albedo);

            bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
            Aabb boundingBox() const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override { return nullptr; }

    private:
            std::shared_ptr<Hittable> _boundary;
            double _negInvDensity;
            std::shared_ptr<Material> _phaseFunction;
    };
};

#endif /* !CONSTANTMEDIUM_HPP_ */
