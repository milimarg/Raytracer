/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_
    #include "Hittable.hpp"
    #include "Onb.hpp"
    #include "Texture.hpp"

namespace rtx
{
    class Sphere : public Hittable {
        public:
            Sphere(
                const Point3 &center,
                double radius,
                std::shared_ptr<Material> mat,
                std::shared_ptr<Texture> normalMap = nullptr
            );
            Sphere(
                const Point3 &center1,
                const Point3 &center2,
                double radius,
                std::shared_ptr<Material> mat,
                std::shared_ptr<Texture> normalMap = nullptr
            );

            bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
            Aabb boundingBox() const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override;

    private:
            Point3 _center1;
            double _radius;
            std::shared_ptr<Material> _mat;
            bool _isMoving;
            Vec3 _centerVec;
            Aabb _bbox;

            std::shared_ptr<Texture> _normalMap;

            Vec3 getNormalFromMap(const HitRecord &rec) const;

            Point3 sphereCenter(double time) const;
            static void getSphereUv(const Point3 &p, double &u, double &v);
            static Vec3 randomToSphere(double radius, double distanceSquared);
    };
};

#endif /* !SPHERE_HPP_ */
