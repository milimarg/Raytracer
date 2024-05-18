/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** RotateY
*/

#ifndef ROTATEY_HPP_
    #define ROTATEY_HPP_
    #include "Hittable.hpp"

namespace rtx
{
    class RotateY : public Hittable {
        public:
            RotateY(std::shared_ptr<Hittable> object, double angle);

            bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
            Aabb boundingBox() const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override {return nullptr; }

        private:
            std::shared_ptr<Hittable> _object;
            double _sinTheta;
            double _cosTheta;
            Aabb _bbox;

            Point3 rotate(const Point3 &p) const;
    };
};

#endif /* !ROTATEY_HPP_ */
