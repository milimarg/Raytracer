/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Metal
*/

#ifndef METAL_HPP_
    #define METAL_HPP_
    #include "Material.hpp"
    #include "ScatterRecord.hpp"

namespace rtx
{
    class Metal : public Material {
        public:
            Metal(const Color &albedo, double fuzz);

            bool scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const override;

        private:
            Color _albedo;
            double _fuzz;
    };
};

#endif /* !METAL_HPP_ */
