/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** TranslationMatrix.cpp
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
#include "Math/Matrix/Matrix.hpp"

namespace rtx
{
    std::shared_ptr<Hittable> Scene::registerTranslationMatrix(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable)
    {
        Vec3 posVec;
        static const std::string nameToFind = "position";

        if (!primitive.exists(nameToFind)) {
            throw Error("Scene - registerTranslationMatrix - Failed to apply translationMatrix: " + nameToFind + " not found");
            return hittable;
        }

        const libconfig::Setting &position = primitive[nameToFind.c_str()];
        position.lookupValue("x", posVec[0]);
        position.lookupValue("y", posVec[1]);
        position.lookupValue("z", posVec[2]);

        Matrix matrix;

        matrix.applyTranslation(posVec);

        return hittable->applyTransformation(matrix);
    }
};
