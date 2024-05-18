/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** SfmlImage
*/

#include "SfmlImage.hpp"
#include "../Includes/Error/Error.hpp"

namespace rtx
{
    SfmlImage::SfmlImage(const std::string &imageFilename)
    {
        if (!load(imageFilename))
            throw Error("SfmlImage - SfmlImage: Could not load image file '" + imageFilename + "'.");
    }

    bool SfmlImage::load(const std::string &imageFilename)
    {
        if (!_image.loadFromFile(imageFilename)) {
            throw Error("SfmlImage - load: Could not load image file '" + imageFilename + "'.");
            return false;
        }
        return true;
    }

    int SfmlImage::width() const
    {
        return _image.getSize().x;
    }

    int SfmlImage::height() const
    {
        return _image.getSize().y;
    }

    sf::Color SfmlImage::pixelData(int x, int y) const
    {
        int clampedX = std::clamp(x, 0, width() - 1);
        int clampedY = std::clamp(y, 0, height() - 1);
        return _image.getPixel(clampedX, clampedY);
    }
};
