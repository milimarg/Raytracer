/*
** EPITECH PROJECT, 2024
** raytracerPreparations++
** File description:
** Onb
*/

#ifndef ONB_HPP_
    #define ONB_HPP_
    #include "Vec3.hpp"

namespace rtx
{
    class Onb {
        public:
            Onb() = default;

            Vec3 operator[](int i) const;
            Vec3 &operator[](int i);

            Vec3 u() const;
            Vec3 v() const;
            Vec3 w() const;

            Vec3 local(double a, double b, double c) const;
            Vec3 local(const Vec3 &a) const;
            void buildFromW(const Vec3 &w);

        private:
            Vec3 _axis[3];
    };
};

#endif /* !ONB_HPP_ */
