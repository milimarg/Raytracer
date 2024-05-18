/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Hittable
*/

#ifndef HITTABLE_HPP_
    #define HITTABLE_HPP_
    #include "Aabb.hpp"
    #include "HitRecord.hpp"
    #include "Math/Matrix/Matrix.hpp"
    #include "Factory.hpp"

namespace rtx
{
    class Material;

    class Hittable {
        public:
            virtual ~Hittable() = default;

            virtual bool hit(const Ray &r, Interval rayT, HitRecord &rec) const = 0;
            virtual Aabb boundingBox() const = 0;
            virtual double pdfValue(const Point3 &origin, const Vec3 &direction) const = 0;
            virtual Vec3 random(const Point3 &origin) const = 0;
            virtual std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) = 0;
    };
};

#endif /* !HITTABLE_HPP_ */
