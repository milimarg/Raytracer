/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Isotropic
*/

#ifndef ISOTROPIC_HPP_
    #define ISOTROPIC_HPP_
    #include "Material.hpp"
    #include "ScatterRecord.hpp"

namespace rtx
{
    class Isotropic : public Material {
        public:
            Isotropic(const Color &albedo);
            Isotropic(std::shared_ptr<Texture> tex);

            bool scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const override;
            double scatteringPdf(const Ray &rIn, const HitRecord& rec, const Ray &scattered) const override;

        private:
            std::shared_ptr<Texture> _tex;
    };
}

#endif /* !ISOTROPIC_HPP_ */
