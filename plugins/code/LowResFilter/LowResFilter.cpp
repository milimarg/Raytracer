/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** LowResFilter
*/

#include "LowResFilter.hpp"
#include "Color.hpp"

namespace rtx
{
    std::vector<rtx::Color> LowResFilter::applyFilter(const std::vector<rtx::Color> &pixelBuffer, size_t imageWidth, size_t imageHeight, double threshold) const
    {
        std::vector<Color> smoothedPixelBuffer(imageWidth * imageHeight);

        for (size_t j = 0; j < imageHeight; ++j) {
            for (size_t i = 0; i < imageWidth; ++i) {
                Color centerColor = pixelBuffer[j * imageWidth + i];
                Color sumColor(0, 0, 0);
                int numNeighbors = 0;

                for (int dj = -1; dj <= 1; ++dj) {
                    for (int di = -1; di <= 1; ++di) {
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < imageWidth && nj >= 0 && nj < imageHeight) {
                            sumColor += pixelBuffer[nj * imageWidth + ni];
                            numNeighbors++;
                        }
                    }
                }

                Color smoothedColor = sumColor / numNeighbors;
                double diff = colorDistance(centerColor, smoothedColor);

                if (diff > threshold) {
                    smoothedPixelBuffer[j * imageWidth + i] = smoothedColor;
                } else {
                    smoothedPixelBuffer[j * imageWidth + i] = centerColor;
                }
            }
        }

        return smoothedPixelBuffer;
    }

    double LowResFilter::colorDistance(const Color& c1, const Color& c2) const
    {
        double dr = c1.r() - c2.r();
        double dg = c1.g() - c2.g();
        double db = c1.b() - c2.b();
        return std::sqrt(dr * dr + dg * dg + db * db);
    }
}
