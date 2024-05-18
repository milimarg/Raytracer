/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** NoiseTexture
*/

#ifndef NOISETEXTURE_HPP_
    #define NOISETEXTURE_HPP_
    #include "Texture.hpp"

namespace rtx
{
    class NoiseTexture : public Texture {
        public:
            NoiseTexture() = default;
            NoiseTexture(double scale, int type = -1);

            Color value(double u, double v, const Point3 &p) const override;

        private:
            Perlin _noise;
            double _scale;
            int _type;
    };
};

#endif /* !NOISETEXTURE_HPP_ */
