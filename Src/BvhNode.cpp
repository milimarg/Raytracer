/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** BvhNode
*/

#include "BvhNode.hpp"
#include "Factory.hpp"

namespace rtx
{
    BvhNode::BvhNode(HittableList list)
    : BvhNode(list._objects, 0, list._objects.size())
    {
    }

    BvhNode::BvhNode(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end)
    {
        _bbox = Aabb::_empty;
        for (size_t objectIndex = start; objectIndex < end; objectIndex++)
            _bbox = Aabb(_bbox, objects[objectIndex]->boundingBox());

        int axis = _bbox.longestAxis();

        auto comparator = (axis == 0) ? boxXCompare
                        : (axis == 1) ? boxYCompare
                                    : boxZCompare;

        size_t objectSpan = end - start;

        if (objectSpan == 0) {
            _left = nullptr;
            _right = nullptr;
            return;
        }

        if (objectSpan == 1) {
            _left = _right = objects[start];
        } else if (objectSpan == 2) {

            _left = objects[start];
            _right = objects[start + 1];
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + objectSpan /2;
            _left = Factory::createHittable<BvhNode>(objects, start, mid);
            _right = Factory::createHittable<BvhNode>(objects, mid, end);
        }
    }

    bool BvhNode::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
    {
        if (!_bbox.hit(r, ray_t))
            return false;

        bool hit_left = _left->hit(r, ray_t, rec);
        bool hit_right = _right->hit(r, Interval(ray_t._min, hit_left ? rec._t : ray_t._max), rec);

        return hit_left || hit_right;
    }

    Aabb BvhNode::boundingBox() const
    {
        return _bbox;
    }

    double BvhNode::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        if (!_bbox.hit(Ray(origin, direction), Interval(0, Math::_infinity)))
            return 0.0;

        double pdfLeft = _left->pdfValue(origin, direction);
        double pdfRight = _right->pdfValue(origin, direction);

        double pdfTotal = pdfLeft + pdfRight;
        return pdfTotal * 0.5;
    }

    Vec3 BvhNode::random(const Point3 &origin) const
    {
        if (!_bbox.hit(Ray(origin, Vec3(1, 0, 0)), Interval(0, Math::_infinity)))
            return Vec3(0, 1, 0);

        if (Math::randomDouble() < 0.5) {
            return _left->random(origin);
        } else {
            return _right->random(origin);
        }
    }

    bool BvhNode::boxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis_index)
    {
        auto a_axis_interval = a->boundingBox().axisInterval(axis_index);
        auto b_axis_interval = b->boundingBox().axisInterval(axis_index);
        return a_axis_interval._min < b_axis_interval._min;
    }

    bool BvhNode::boxXCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
        return boxCompare(a, b, 0);
    }

    bool BvhNode::boxYCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
        return boxCompare(a, b, 1);
    }

    bool BvhNode::boxZCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
        return boxCompare(a, b, 2);
    }
};
