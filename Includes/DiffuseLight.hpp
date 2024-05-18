/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** DiffuseLight
*/

#ifndef DIFFUSELIGHT_HPP_
    #define DIFFUSELIGHT_HPP_
    #include "Material.hpp"
    #include "ScatterRecord.hpp"

namespace rtx
{
    class DiffuseLight : public Material {
        public:
            DiffuseLight(std::shared_ptr<Texture> tex);
            DiffuseLight(const Color &emit);

            Color emitted(const Ray &rIn, const HitRecord &rec, double u, double v, const Point3 &p) const override;

        private:
            std::shared_ptr<Texture> _tex;
    };
};

#endif /* !DIFFUSELIGHT_HPP_ */
