/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
    #define HITRECORD_HPP_
    #include "Aabb.hpp"

namespace rtx
{
    class Material;

    class HitRecord {
        public:
            Point3 _p;
            Vec3 _normal;
            std::shared_ptr<Material> _mat;
            double _t;
            double _u;
            double _v;
            bool _frontFace;

            void setFaceNormal(const Ray &r, const Vec3 &outwardNormal);
    };
}

#endif /* !HITRECORD_HPP_ */
