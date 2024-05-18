/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** ImageTexture
*/

#ifndef IMAGETEXTURE_HPP_
    #define IMAGETEXTURE_HPP_
    #include "Texture.hpp"
    #include "Interval.hpp"
    #include "SfmlImage.hpp"

namespace rtx
{
    class ImageTexture : public Texture {
        public:
            ImageTexture(const std::string &filename,
                         const double rotationAngleX = 0,
                         const double rotationAngleY = 0);

            Color value(double u, double v, const Point3 &p) const override;
            void setRotationAngleX(const double rotationAngleX);
            void setRotationAngleY(const double rotationAngleY);

        private:
            SfmlImage _image;
            const int _minInterval = 0;
            const int _maxInterval = 1;
            const double _shiftPerAngle = 0.0022;
            double _rotationAngleX = 0;
            double _rotationAngleY = 0;
    };
};

#endif /* !IMAGETEXTURE_HPP_ */
