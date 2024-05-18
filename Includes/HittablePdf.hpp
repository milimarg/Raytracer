/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** HittablePdf
*/

#ifndef HITTABLEPDF_HPP_
    #define HITTABLEPDF_HPP_
    #include "Pdf.hpp"

namespace rtx
{
    class HittablePdf : public Pdf {
        public:
            HittablePdf(const Hittable &objects, const Point3 &origin);

            double value(const Vec3 &direction) const override;
            Vec3 generate() const override;

        private:
            const Hittable &_objects;
            Point3 _origin;
    };
};

#endif /* !HITTABLEPDF_HPP_ */
