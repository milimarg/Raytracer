/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** RotationMatrix.cpp
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
    std::shared_ptr<Hittable> Scene::registerRotationMatrix(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable)
    {
        Vec3 posVec;
        double angle = 0;
        std::string name;
        static const std::string nameToFind = "angle";

        if (!primitive.exists(nameToFind)) {
            throw Error("Scene - registerRotationMatrix - Failed to apply RotationMatrix: " + nameToFind + " not found");
            return hittable;
        }

        primitive.lookupValue("name", name);
        primitive.lookupValue(nameToFind.c_str(), angle);

        Matrix matrix;

        if (name == "RotationX")
            matrix.applyRotationX(angle);
        if (name == "RotationY")
            matrix.applyRotationY(angle);
        if (name == "RotationZ")
            matrix.applyRotationZ(angle);
        return hittable->applyTransformation(matrix);
    }
};
