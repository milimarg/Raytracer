/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** MedianFilter
*/

#ifndef MEDIANFILTER_HPP_
    #define MEDIANFILTER_HPP_

    #include <iostream>
    #include <memory>
    #include "IPlugin.hpp"

namespace rtx
{
    class MedianFilter : public IPlugin {
        public:
            MedianFilter() = default;
            ~MedianFilter() = default;

            std::vector<rtx::Color> applyFilter(const std::vector<rtx::Color> &pixelBuffer, size_t imageWidth, size_t imageHeight, double threshold) const override;
            double luminance(const Color &color) const;
            Color medianFilter(const std::vector<Color> &neighborhood) const;
    };
}

extern "C" {
    std::string getType() {
        return "filter";
    }

    std::unique_ptr<rtx::IPlugin> entryPoint() {
        return std::make_unique<rtx::MedianFilter>();
    }
}

#endif /* !MEDIANFILTER_HPP_ */
