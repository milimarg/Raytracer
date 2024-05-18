/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Torus
*/

#ifndef TORUS_HPP_
    #define TORUS_HPP_
    #include "Hittable.hpp"

namespace rtx {
    class Torus : public Hittable {
        public:
            Torus(const Point3 &center, double majorRadius, double minorRadius, std::shared_ptr<Material> mat);

            bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
            Aabb boundingBox() const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override;
        protected:
        private:
            Point3 _center;
            double _majorRadius;
            double _minorRadius;
            std::shared_ptr<Material> _mat;
            Aabb _bbox;
    };
}

#endif /* !TORUS_HPP_ */
