/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** HittableList
*/

#ifndef HITTABLELIST_HPP_
    #define HITTABLELIST_HPP_
    #include "Hittable.hpp"
    #include <vector>

namespace rtx
{
    class HittableList : public Hittable {
        public:
            std::vector<std::shared_ptr<Hittable>> _objects;

            HittableList() = default;
            HittableList(std::shared_ptr<Hittable> object);

            void clear();
            void add(std::shared_ptr<Hittable> object);

            bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
            Aabb boundingBox() const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override;

            Aabb _bbox;
        private:

    };
};

#endif /* !HITTABLELIST_HPP_ */
