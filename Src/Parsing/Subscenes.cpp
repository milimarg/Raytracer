/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** registerSubscenes.cpp
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

namespace fs = std::filesystem;

namespace rtx
{
    void Scene::registerSubscenes(const libconfig::Setting &setting)
    {
        for (int i = 0; i < setting.getLength(); ++i) {
            const libconfig::Setting &subscenePath = setting[i];
            std::string subsceneFilepath;
            if (subscenePath.lookupValue("file", subsceneFilepath)) {
                if (fs::exists(subsceneFilepath)) {
                    libconfig::Config subsceneConfig;
                    try {
                        subsceneConfig.readFile(subsceneFilepath.c_str());
                        const libconfig::Setting &primitivesSetting = subsceneConfig.lookup("primitives");
                        registerPrimitives(primitivesSetting);
                    } catch (const libconfig::FileIOException &exception) {
                        throw Error("Scene - registerSubscenes - Couldn't open subscene file: " + subsceneFilepath);
                    } catch (const libconfig::ParseException &exception) {
                        throw Error(std::string("Scene - registerSubscenes - Couldn't parse subscene file: ")
                        + exception.getFile() + ":" + std::to_string(exception.getLine()) + " - " + exception.getError());
                    }
                } else {
                    throw Error("Scene - registerSubscenes - Subscene file not found: " + subsceneFilepath);
                }
            }
        }
    }
};
