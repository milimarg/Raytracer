/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** SpherePdf
*/

#ifndef SPHEREPDF_HPP_
    #define SPHEREPDF_HPP_
    #include "Pdf.hpp"

namespace rtx
{
    class SpherePdf : public Pdf {
        public:
            SpherePdf() = default;

            double value(const Vec3 &direction) const override;
            Vec3 generate() const override;
    };
};

#endif /* !SPHEREPDF_HPP_ */
