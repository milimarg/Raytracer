/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** IPlugin
*/

#ifndef IPLUGIN_HPP_
    #define IPLUGIN_HPP_
    #include <vector>

namespace rtx
{
    class Color;

    class IPlugin {
        public:
            virtual ~IPlugin() = default;

            virtual std::vector<rtx::Color> applyFilter(const std::vector<rtx::Color> &pixelBuffer, size_t imageWidth, size_t imageHeight, double threshold) const = 0;
    };
}

#endif /* !IPLUGIN_HPP_ */
