/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** SfmlTexture
*/

#ifndef SFMLIMAGE_HPP_
    #define SFMLIMAGE_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include <algorithm>

namespace rtx
{
    class SfmlImage {
        public:
            SfmlImage() = default;
            SfmlImage(const std::string &imageFilename);

            bool load(const std::string &imageFilename);
            int width() const;
            int height() const;
            sf::Color pixelData(int x, int y) const;

        private:
            sf::Image _image;
    };
}

#endif /* !SFMLIMAGE_HPP_ */
