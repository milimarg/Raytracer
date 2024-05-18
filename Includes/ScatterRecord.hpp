/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** ScatterRecord
*/

#ifndef SCATTERRECORD_HPP_
    #define SCATTERRECORD_HPP_
    #include "Color.hpp"
    #include "Pdf.hpp"

namespace rtx
{
    class ScatterRecord {
        public:
            Color _attenuation;
            std::shared_ptr<Pdf> _pdfPtr;
            bool _skipPdf;
            Ray _skipPdfRay;
    };
};

#endif /* !SCATTERRECORD_HPP_ */
