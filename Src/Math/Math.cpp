/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Math.cpp
*/

#include "Math/Math.hpp"

namespace rtx
{
    double Math::degreesToRadians(double degrees)
    {
        return degrees * Math::_pi / 180.0;
    }

    double Math::randomDouble()
    {
        static thread_local std::random_device rd;
        static thread_local std::mt19937 generator(rd());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    }

    double Math::randomDouble(double min, double max)
    {
        static thread_local std::random_device rd;
        static thread_local std::mt19937 generator(rd());
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }

    int Math::randomInt(int min, int max)
    {
        return int(randomDouble(min, max + 1));
    }

    const double Math::_infinity = std::numeric_limits<double>::infinity();
    const double Math::_pi = 3.1415926535897932385;
};
