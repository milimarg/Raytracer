/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
    #define TEXTURE_HPP_
    #include "Color.hpp"
    #include "Perlin.hpp"

namespace rtx
{
    class Texture {
        public:
            virtual ~Texture() = default;

            virtual Color value(double u, double v, const Point3 &p) const = 0;
    };
};

#endif /* !TEXTURE_HPP_ */
