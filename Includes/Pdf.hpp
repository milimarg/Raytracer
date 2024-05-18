/*
** EPITECH PROJECT, 2024
** raytracerPreparations++
** File description:
** Pdf
*/

#ifndef PDF_HPP_
    #define PDF_HPP_
    #include "HittableList.hpp"
    #include "Onb.hpp"

namespace rtx
{
    class Pdf {
        public:
            virtual ~Pdf() {}

            virtual double value(const Vec3 &direction) const = 0;
            virtual Vec3 generate() const = 0;
    };
};

#endif /* !PDF_HPP_ */
