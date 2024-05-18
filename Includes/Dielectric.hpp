/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Dielectric
*/

#ifndef DIELECTRIC_HPP_
    #define DIELECTRIC_HPP_
    #include "Material.hpp"
    #include "ScatterRecord.hpp"

namespace rtx
{
    class Dielectric : public Material {
        public:
            Dielectric(double refractionIndex);

            bool scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const override;

        private:
            double _refractionIndex;

            static double reflectance(double cosine, double refractionIndex);
    };
};

#endif /* !DIELECTRIC_HPP_ */
