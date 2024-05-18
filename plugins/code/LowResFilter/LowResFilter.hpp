/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** LowResFilter
*/

#ifndef LOWRESFILTER_HPP_
    #define LOWRESFILTER_HPP_

    #include <iostream>
    #include <memory>
    #include "IPlugin.hpp"

namespace rtx
{
    class LowResFilter : public IPlugin {
        public:
            LowResFilter() = default;
            ~LowResFilter() = default;

            std::vector<rtx::Color> applyFilter(const std::vector<rtx::Color> &pixelBuffer, size_t imageWidth, size_t imageHeight, double threshold) const override;
            double colorDistance(const Color &c1, const Color &c2) const;
    };
}

extern "C" {
    std::string getType() {
        return "filter";
    }

    std::unique_ptr<rtx::IPlugin> entryPoint() {
        return std::make_unique<rtx::LowResFilter>();
    }
}

#endif /* !LOWRESFILTER_HPP_ */
