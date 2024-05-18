/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Material
*/

#ifndef MATERIAL_HPP_
    #define MATERIAL_HPP_
    #include "Pdf.hpp"
    #include "Texture.hpp"

namespace rtx
{
    class HitRecord;
    class ScatterRecord;

    class Material {
        public:
            virtual ~Material() = default;

            virtual Color emitted(const Ray &rIn, const HitRecord &rec, double u, double v, const Point3 &p) const;
            virtual bool scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const;
            virtual double scatteringPdf(const Ray &RIn, const HitRecord &rec, const Ray &scattered) const;
    };
}

#endif /* !MATERIAL_HPP_ */
