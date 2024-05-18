/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Math.hpp
*/

#ifndef B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_MATH_HPP
    #define B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_MATH_HPP
    #include <cmath>
    #include <cstdlib>
    #include <ctime>
    #include <iostream>
    #include <limits>
    #include <memory>
    #include <thread>
    #include <random>

namespace rtx
{
    class Math {
    public:
        static double degreesToRadians(double degrees);
        static double randomDouble();
        static double randomDouble(double min, double max);
        static int randomInt(int min, int max);

        static const double _infinity;
        static const double _pi;
    };
};

#endif //B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_MATH_HPP
