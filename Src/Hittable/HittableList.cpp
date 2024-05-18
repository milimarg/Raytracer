/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** HittableList
*/

#include "HittableList.hpp"

namespace rtx
{
    HittableList::HittableList(std::shared_ptr<Hittable> object)
    {
        _objects.push_back(object);
    }

    void HittableList::clear()
    {
        _objects.clear();
    }

    void HittableList::add(std::shared_ptr<Hittable> object)
    {
        _objects.push_back(object);
        _bbox = Aabb(_bbox, object->boundingBox());
    }

    bool HittableList::hit(const Ray &r, Interval rayT, HitRecord &rec) const
    {
        HitRecord tempRec;
        bool hitAnything = false;
        auto closestSoFar = rayT._max;

        for (const auto &object : _objects) {
            if (object->hit(r, Interval(rayT._min, closestSoFar), tempRec)) {
                hitAnything = true;
                closestSoFar = tempRec._t;
                rec = tempRec;
            }
        }
        return hitAnything;
    }

    Aabb HittableList::boundingBox() const
    {
        return _bbox;
    }

    double HittableList::pdfValue(const Point3 &origin, const Vec3 &direction) const
    {
        auto weight = 1.0 / _objects.size();
        auto sum = 0.0;

        for (const auto &object : _objects)
            sum += weight * object->pdfValue(origin, direction);
        return sum;
    }

    Vec3 HittableList::random(const Point3 &origin) const
    {
        auto int_size = int(_objects.size());
        return _objects[Math::randomInt(0, int_size-1)]->random(origin);
    }

    std::shared_ptr<Hittable> HittableList::applyTransformation(const Matrix &matrix)
    {
        std::vector<std::shared_ptr<Hittable>> objectsTemp;

        for (auto &object : _objects)
            objectsTemp.push_back(object->applyTransformation(matrix));
        _objects.clear();

        auto hl = Factory::createMaterial<HittableList>(objectsTemp[0]);
        bool first = 1;
        for (auto &object : objectsTemp) {
            if (first) {
                first = 0;
                continue;
            }
            hl->add(object);
        }
        return hl;
    }
};
