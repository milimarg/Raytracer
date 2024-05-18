/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** registerPrimitives.cpp
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
    void Scene::registerPrimitives(const libconfig::Setting &primitives)
    {
        static const std::unordered_map<std::size_t, std::function<void(const libconfig::Setting&)>> registrationMap = {
            {hash("spheres"), [this](const libconfig::Setting &setting) { registerSphere(setting); }},
            {hash("quads"), [this](const libconfig::Setting &setting) { registerQuad(setting, Quad::Type::STANDARD); }},
            {hash("boxes"), [this](const libconfig::Setting &setting) { registerBox(setting); }},
            {hash("cylinders"), [this](const libconfig::Setting &setting) { registerCylinder(setting); }},
            {hash("cones"), [this](const libconfig::Setting &setting) { registerCone(setting); }},
            {hash("unlimitedcylinders"), [this](const libconfig::Setting &setting) { registerUnlimitedCylinder(setting); }},
            {hash("unlimitedcones"), [this](const libconfig::Setting &setting) { registerUnlimitedCone(setting); }},
            {hash("obj"), [this](const libconfig::Setting &setting) { registerObj(setting); }},
            {hash("triangles"), [this](const libconfig::Setting &setting) { registerTriangle(setting); }},
            {hash("torus"), [this](const libconfig::Setting &setting) { registerTorus(setting); }},
            {hash("lights"), [this](const libconfig::Setting &setting) { registerQuad(setting, Quad::Type::LIGHT); }}
        };

        for (const libconfig::Setting &element : primitives) {
            const std::string name(element.getName());
            auto hashValue = hash(name.c_str());
            auto registrationFunction = registrationMap.find(hashValue);
            if (registrationFunction != registrationMap.end())
                for (int i = 0; i < element.getLength(); i += 1)
                    registrationFunction->second(element[i]);
        }
    }
};
