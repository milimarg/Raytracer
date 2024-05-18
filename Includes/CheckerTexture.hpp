/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** CheckerTexture
*/

#ifndef CHECKERTEXTURE_HPP_
    #define CHECKERTEXTURE_HPP_
    #include "SolidColor.hpp"

namespace rtx
{
    class CheckerTexture : public Texture {
        public:
            CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
            CheckerTexture(double scale, const Color &c1, const Color &c2);

            Color value(double u, double v, const Point3 &p) const override;

        private:
            double _invScale;
            std::shared_ptr<Texture> _even;
            std::shared_ptr<Texture> _odd;
    };
};

#endif /* !CHECKERTEXTURE_HPP_ */
