/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Translate
*/

#ifndef TRANSLATE_HPP_
    #define TRANSLATE_HPP_
    #include "Hittable.hpp"

namespace rtx
{
    class Translate : public Hittable {
        public:
            Translate(std::shared_ptr<Hittable> object, const Vec3 &offset);

            bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;
            Aabb boundingBox() const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override {return nullptr; }

        private:
            std::shared_ptr<Hittable> _object;
            Vec3 _offset;
            Aabb _bbox;
            Matrix _matrix;
    };
};

#endif /* !TRANSLATE_HPP_ */
