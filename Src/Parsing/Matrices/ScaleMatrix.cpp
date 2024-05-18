/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** ScaleMatrix.cpp
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
    std::shared_ptr<Hittable> Scene::registerScale(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable)
    {
        Vec3 scaleVec;
        double scaleValue = 0;
        static const std::string nameToFind = "scale";

        if (!primitive.exists(nameToFind)) {
            throw Error("Scene - registerScale - Failed to apply scaleMatrix: " + nameToFind + " not found");
            return hittable;
        }

        const libconfig::Setting &scale = primitive[nameToFind.c_str()];
        Matrix matrix;

        if (scale.getType() == libconfig::Setting::TypeFloat) {
            primitive.lookupValue(nameToFind.c_str(), scaleValue);
            matrix.applyScale(scaleValue);
        }
        if (scale.getType() == libconfig::Setting::TypeGroup) {
            scale.lookupValue("x", scaleVec[0]);
            scale.lookupValue("y", scaleVec[1]);
            scale.lookupValue("z", scaleVec[2]);
            matrix.applyScale(scaleVec);
        }
        return hittable->applyTransformation(matrix);
    }
};
