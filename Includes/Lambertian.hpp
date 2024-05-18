/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
    #define LAMBERTIAN_HPP_
    #include "Material.hpp"
    #include "ScatterRecord.hpp"

namespace rtx
{
    class Lambertian : public Material {
        public:
            Lambertian(const Color &albedo);
            Lambertian(std::shared_ptr<Texture> tex);

            bool scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const override;
            double scatteringPdf(const Ray & rIn, const HitRecord &rec, const Ray &scattered) const override;

        private:
            std::shared_ptr<Texture> _tex;
    };
};

#endif /* !LAMBERTIAN_HPP_ */
