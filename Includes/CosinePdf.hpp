/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** CosinePdf
*/

#ifndef COSINEPDF_HPP_
    #define COSINEPDF_HPP_
    #include "Pdf.hpp"

namespace rtx
{
    class CosinePdf : public Pdf {
        public:
            CosinePdf(const Vec3 &w);

            double value(const Vec3 &direction) const override;
            Vec3 generate() const override;

        private:
            Onb _uvw;
    };
};

#endif /* !COSINEPDF_HPP_ */
