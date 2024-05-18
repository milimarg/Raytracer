/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Interval
*/

#ifndef INTERVAL_HPP_
    #define INTERVAL_HPP_
    #include "Math/Math.hpp"

namespace rtx
{
    class Interval {
        public:
            double _min;
            double _max;

            Interval();
            Interval(double min, double max);
            Interval(const Interval &a, const Interval &b);

            double size() const;
            bool contains(double x) const;
            bool surrounds(double x) const;
            double clamp(double x) const;
            double overflow(double x) const;
            Interval expand(double delta) const;

            static const Interval _empty;
            static const Interval _universe;
    };

    Interval operator+(const Interval &ival, double displacement);
    Interval operator+(double displacement, const Interval &ival);
};

#endif /* !INTERVAL_HPP_ */
