/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Quad
*/

#ifndef QUAD_HPP_
    #define QUAD_HPP_
    #include "HittableList.hpp"
    #include "Texture.hpp"

namespace rtx
{
    class Quad : public Hittable {
        public:
            enum class Type {
                STANDARD,
                LIGHT
            };

            Quad(
                const Point3 &Q,
                const Vec3 &u,
                const Vec3 &v,
                std::shared_ptr<Material> mat,
                std::shared_ptr<Texture> normalMap = nullptr
            );

            virtual void setBoundingBox();
            virtual bool isInterior(double a, double b, HitRecord &rec) const;

            Aabb boundingBox() const override;
            bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override;
            double pdfValue(const Point3 &origin, const Vec3 &direction) const override;
            Vec3 random(const Point3 &origin) const override;

            static std::shared_ptr<HittableList> box(const Point3 &a, const Point3 &b, std::shared_ptr<Material> mat);

            std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override;

        private:
            Point3 _Q;
            Vec3 _u;
            Vec3 _v;
            Vec3 _w;
            std::shared_ptr<Material> _mat;
            Aabb _bbox;
            Vec3 _normal;
            double _D;
            double _area;

            std::shared_ptr<Texture> _normalMap;

            Vec3 getNormalFromMap(const HitRecord &rec) const;
    };
};

#endif /* !QUAD_HPP_ */
