/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** registerCamera.cpp
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
    void Scene::registerCamera(const libconfig::Setting &cameraLib)
    {
        double x = 0;
        double y = 0;
        double z = 0;

        for (const libconfig::Setting &element : cameraLib) {
            const std::string name(element.getName());
            if (name == "position") {
                element.lookupValue("x", x);
                element.lookupValue("y", y);
                element.lookupValue("z", z);
                _camera._lookfrom = Point3(x, y, z);
            }
            if (name == "observation_position") {
                element.lookupValue("x", x);
                element.lookupValue("y", y);
                element.lookupValue("z", z);
                _camera._lookat = Point3(x, y, z);
            }
            if (name == "rotation") {
                element.lookupValue("x", x);
                element.lookupValue("y", y);
                element.lookupValue("z", z);
            }
        }
        cameraLib.lookupValue("fieldOfView", _camera._vfov);
    }
};
