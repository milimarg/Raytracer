/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Dielectric.cpp
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

    bool Scene::registerDielectric(const libconfig::Setting &primitive, const std::string &mat, std::string &matName)
    {
        double intensity = 0;

        if (!primitive.exists("intensity")) {
            throw Error("Scene - RegisterMaterial: Dielectric: intensity variable not found");
            return true;
        }
        primitive.lookupValue("intensity", intensity);
        matName = mat + std::to_string(intensity);
        _materialMap[matName] = Factory::createMaterial<Dielectric>(intensity);
        return false;
    }
};
