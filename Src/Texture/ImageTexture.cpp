/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** ImageTexture
*/

#include "ImageTexture.hpp"

namespace rtx
{
    ImageTexture::ImageTexture(const std::string &filename,
                               const double rotationAngleX,
                               const double rotationAngleY)
        : _image(filename), _rotationAngleX(rotationAngleX), _rotationAngleY(rotationAngleY)
    {}

    Color ImageTexture::value(double u, double v, const Point3 &p) const
    {
        if (_image.height() <= 0)
            return Color(0,1,1);

        u = Interval(_minInterval, _maxInterval).clamp(u);
        v = (float)_maxInterval - Interval(_minInterval, _maxInterval).clamp(v);

        u += _rotationAngleX * _shiftPerAngle;
        v += _rotationAngleY * _shiftPerAngle;

        u = Interval(_minInterval, _maxInterval).overflow(u);
        v = Interval(_minInterval, _maxInterval).overflow(v);

        int i = int(u * _image.width());
        int j = int(v * _image.height());

        auto pixel = _image.pixelData(i, j);

        auto colorScale = 1.0 / 255.0;
        return Color(colorScale * pixel.r, colorScale * pixel.g, colorScale * pixel.b);
    }

    void ImageTexture::setRotationAngleX(const double rotationAngleX)
    {
        _rotationAngleX = rotationAngleX;
    }

    void ImageTexture::setRotationAngleY(const double rotationAngleY)
    {
        _rotationAngleY = rotationAngleY;
    }
};
