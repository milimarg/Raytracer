/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** ShearMatrix.cpp
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
    std::shared_ptr<Hittable> Scene::registerShear(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable)
    {
        std::string name;
        static const std::string nameToFind = "shear";
        double component1 = 0;
        double component2 = 0;

        primitive.lookupValue("name", name);

        Matrix matrix;

        if (name == "ShearX") {
            if (!primitive.exists("y") || !primitive.exists("z")) {
                throw Error("Scene - registerShear - Failed to apply shearMatrix X: y or z not found");
                return hittable;
            }
            primitive.lookupValue("y", component1);
            primitive.lookupValue("z", component2);
            matrix.applyShearX(component1, component2);
        }
        if (name == "ShearY") {
            if (!primitive.exists("x") || !primitive.exists("z")) {
                throw Error("Scene - registerShear - Failed to apply shearMatrix Y: x or z not found");
                return hittable;
            }
            primitive.lookupValue("x", component1);
            primitive.lookupValue("z", component2);
            matrix.applyShearY(component1, component2);
        }
        if (name == "ShearZ") {
            if (!primitive.exists("x") || !primitive.exists("y")) {
                throw Error("Scene - registerShear - Failed to apply shearMatrix Z: x or y not found");
                return hittable;
            }
            primitive.lookupValue("x", component1);
            primitive.lookupValue("y", component2);
            matrix.applyShearZ(component1, component2);
        }
        return hittable->applyTransformation(matrix);
    }
};
