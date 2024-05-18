/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** MedianFilter
*/

#include "MedianFilter.hpp"
#include "Color.hpp"
#include <algorithm>

namespace rtx
{
    std::vector<rtx::Color> MedianFilter::applyFilter(const std::vector<rtx::Color> &pixelBuffer, size_t imageWidth, size_t imageHeight, double threshold) const
    {
        std::vector<Color> filteredPixelBuffer(imageWidth * imageHeight);
        int lim = (threshold >= 1.9 && threshold <= 2.1) ? 2 : 1;

        for (size_t j = lim; j < imageHeight - lim; ++j) {
            for (size_t i = lim; i < imageWidth - lim; ++i) {
                std::vector<Color> neighborhood;
                for (int dj = -lim; dj <= lim; ++dj)
                    for (int di = -lim; di <= lim; ++di)
                        neighborhood.push_back(pixelBuffer[(j + dj) * imageWidth + (i + di)]);
                filteredPixelBuffer[j * imageWidth + i] = medianFilter(neighborhood);
            }
        }

        return filteredPixelBuffer;
    }

    double MedianFilter::luminance(const Color& color) const
    {
        return 0.2126 * color.r() + 0.7152 * color.g() + 0.0722 * color.b();
    }

    Color MedianFilter::medianFilter(const std::vector<Color>& neighborhood) const
    {
        std::vector<Color> sortedColors(neighborhood);

        std::sort(sortedColors.begin(), sortedColors.end(),
            [&](const Color& c1, const Color& c2) {
                return luminance(c1) < luminance(c2);
            }
        );

        size_t medianIndex = neighborhood.size() / 2;

        return sortedColors[medianIndex];
    }
}
