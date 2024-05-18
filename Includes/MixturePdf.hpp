/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** MixturePdf
*/

#ifndef MIXTUREPDF_HPP_
    #define MIXTUREPDF_HPP_
    #include "Pdf.hpp"

namespace rtx
{
    class MixturePdf : public Pdf {
        public:
            MixturePdf(std::shared_ptr<Pdf> p0, std::shared_ptr<Pdf> p1);

            double value(const Vec3 &direction) const override;
            Vec3 generate() const override;

        private:
            std::shared_ptr<Pdf> _p[2];
    };
};

#endif /* !MIXTUREPDF_HPP_ */
