/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** BvhNode
*/

#ifndef BVHNODE_HPP_
    #define BVHNODE_HPP_
    #include "Aabb.hpp"
    #include "HittableList.hpp"
    #include <algorithm>

namespace rtx
{
    class BvhNode : public Hittable {
        public:
            BvhNode(HittableList list);

            BvhNode(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end);

            bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

            Aabb boundingBox() const override;

            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;

            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override { return nullptr; }

    private:
            std::shared_ptr<Hittable> _left;
            std::shared_ptr<Hittable> _right;
            Aabb _bbox;

            static bool boxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis_index);
            static bool boxXCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
            static bool boxYCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
            static bool boxZCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
    };
};

#endif /* !BVHNODE_HPP_ */
