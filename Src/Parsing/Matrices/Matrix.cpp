/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** registerMatrix.cpp
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Sphere.hpp"
#include "Quad.hpp"
#include "Scene.hpp"
#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "DiffuseLight.hpp"
#include "Metal.hpp"
#include "Isotropic.hpp"

namespace rtx
{
    std::shared_ptr<Hittable> Scene::registerMatrices(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable)
    {
        if (!primitive.exists("matrices"))
            return hittable;

        std::string matrixName;
        std::shared_ptr<Hittable> newHittable(std::move(hittable));

        const libconfig::Setting &matrices = primitive["matrices"];

        for (size_t i = 0; i < matrices.getLength(); i += 1) {
            matrices[i].lookupValue("name", matrixName);
            if (matrixName == "Translation")
                newHittable = registerTranslationMatrix(matrices[i], newHittable);
            if (matrixName == "RotationX" || matrixName == "RotationY" || matrixName == "RotationZ")
                newHittable = registerRotationMatrix(matrices[i], newHittable);
            if (matrixName == "Scale")
                newHittable = registerScale(matrices[i], newHittable);
            if (matrixName == "ShearX" || matrixName == "ShearY" || matrixName == "ShearZ")
                newHittable = registerShear(matrices[i], newHittable);

        }
        return newHittable;
    }
};
