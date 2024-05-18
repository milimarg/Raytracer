/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Interval.cpp
*/

#include "Interval.hpp"

namespace rtx
{
    const Interval Interval::_empty = Interval(+Math::_infinity, -Math::_infinity);
    const Interval Interval::_universe = Interval(-Math::_infinity, +Math::_infinity);

    Interval operator+(const Interval &ival, double displacement)
    {
        return Interval(ival._min + displacement, ival._max + displacement);
    }

    Interval operator+(double displacement, const Interval &ival)
    {
        return ival + displacement;
    }

    Interval::Interval()
        : _min(+Math::_infinity), _max(-Math::_infinity) {}

    Interval::Interval(double min, double max)
        : _min(min), _max(max) {}

    Interval::Interval(const Interval &a, const Interval &b)
    {
        _min = a._min <= b._min ? a._min : b._min;
        _max = a._max >= b._max ? a._max : b._max;
    }

    double Interval::size() const
    {
        return _max - _min;
    }

    bool Interval::contains(double x) const
    {
        return _min <= x && x <= _max;
    }

    bool Interval::surrounds(double x) const
    {
        return _min < x && x < _max;
    }

    double Interval::clamp(double x) const
    {
        if (x < _min)
            return _min;
        if (x > _max)
            return _max;
        return x;
    }

    double Interval::overflow(double x) const
    {
        if (x < _min)
            return _max - std::abs(x);
        if (x > _max)
            return x - _max;
        return x;
    }

    Interval Interval::expand(double delta) const
    {
        auto padding = delta / 2;
        return Interval(_min - padding, _max + padding);
    }
};
