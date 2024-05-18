/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** SolidColor
*/

#ifndef SOLIDCOLOR_HPP_
    #define SOLIDCOLOR_HPP_
    #include "Texture.hpp"

namespace rtx
{
    class SolidColor : public Texture {
        public:
            SolidColor(const Color &albedo);
            SolidColor(double red, double green, double blue);

            Color value(double u, double v, const Point3 &p) const override;

        private:
            Color _albedo;
    };
};

#endif /* !SOLIDCOLOR_HPP_ */
