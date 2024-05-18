/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Materials.cpp
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

    bool Scene::registerMaterial(const libconfig::Setting &primitive, const std::string &mat, std::string &matName)
    {
        if (_materialMap.find(mat) != _materialMap.end())
            return false;
        if (mat == "Dielectric")
            return registerDielectric(primitive, mat, matName);
        if (mat == "Lambertian" || "DiffuseLight" || "Metal" || "Isotropic")
            return colorBasedMaterial(primitive, mat, matName);
        if (mat == "m") {
            _materialMap[mat] = Factory::createMaterial<Material>();
            return false;
        }
        throw Error("Scene - registerMaterial - Scene: Failed to create material \"" + mat + "\" (name not known)");
        return true;
    }
};
