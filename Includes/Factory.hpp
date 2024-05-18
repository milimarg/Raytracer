/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Raytracer.hpp
*/

#ifndef B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_RAYTRACER_HPP
    #define B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_RAYTRACER_HPP
    #include <memory>

namespace rtx
{
    class Factory {
        public:
            template<typename MaterialType, typename... Args>
            static std::shared_ptr<MaterialType> createMaterial(Args&&... args)
            {
                return std::make_shared<MaterialType>(std::forward<Args>(args)...);
            }

            template<typename HittableType, typename... Args>
            static std::shared_ptr<HittableType> createHittable(Args&&... args)
            {
                return std::make_shared<HittableType>(std::forward<Args>(args)...);
            }

            template<typename TransformationType, typename... Args>
            static std::shared_ptr<TransformationType> applyTransformation(Args&&... args)
            {
                return std::make_shared<TransformationType>(std::forward<Args>(args)...);
            }

            template<typename TextureType, typename... Args>
            static std::shared_ptr<TextureType> createTexture(Args&&... args)
            {
                return std::make_shared<TextureType>(std::forward<Args>(args)...);
            }

            template<typename PdfType, typename... Args>
            static std::shared_ptr<PdfType> createPdf(Args&&... args)
            {
                return std::make_shared<PdfType>(std::forward<Args>(args)...);
            }
    };
};

#endif //B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_RAYTRACER_HPP
