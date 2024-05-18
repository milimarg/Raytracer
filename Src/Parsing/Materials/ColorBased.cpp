/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** colorBased.cpp
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
    bool Scene::colorBasedMaterial(const libconfig::Setting &primitive, const std::string &mat, std::string &matName)
    {
        Color colorVec;
        double fuzz;

        if (!primitive.exists("color")) {
            throw Error("Scene - colorBasedMaterial - RegisterMaterial: " + mat + ": color variable not found");
            return true;
        }
        const libconfig::Setting &color = primitive["color"];
        if (!color.exists("r") || !color.exists("g") || !color.exists("b")) {
            throw Error("Scene - colorBasedMaterial - RegisterMaterial: " + mat + ": all color components not found");
            return true;
        }
        color.lookupValue("r", colorVec[0]);
        color.lookupValue("g", colorVec[1]);
        color.lookupValue("b", colorVec[2]);

        matName = mat + std::to_string(colorVec[0]) + ";"
                  + std::to_string(colorVec[1]) + ";"
                  + std::to_string(colorVec[2]);

        if (mat == "Lambertian") {
            std::shared_ptr<Texture> texture = getMaterialTexture(primitive, mat, matName);

            if (texture) {
                _materialMap[matName] = Factory::createMaterial<Lambertian>(texture);
            } else {
                _materialMap[matName] = Factory::createMaterial<Lambertian>(colorVec);
            }
        }
        if (mat == "DiffuseLight") {
            std::shared_ptr<Texture> texture = getMaterialTexture(primitive, mat, matName);

            if (texture) {
                _materialMap[matName] = Factory::createMaterial<DiffuseLight>(texture);
            } else {
                _materialMap[matName] = Factory::createMaterial<DiffuseLight>(colorVec);
            }
        }
        if (mat == "Isotropic") {
            std::shared_ptr<Texture> texture = getMaterialTexture(primitive, mat, matName);

            if (texture) {
                _materialMap[matName] = Factory::createMaterial<Isotropic>(texture);
            } else {
                _materialMap[matName] = Factory::createMaterial<Isotropic>(colorVec);
            }
        }
        if (mat == "Metal") {
            if (!primitive.exists("fuzz")) {
                throw Error("Scene - colorBasedMaterial - RegisterMaterial: " + mat + ": fuzz variable not found");
                return true;
            }
            primitive.lookupValue("fuzz", fuzz);
            matName += ";" + std::to_string(fuzz);
            _materialMap[matName] = Factory::createMaterial<Metal>(colorVec, fuzz);
        }
        return false;
    }
};
