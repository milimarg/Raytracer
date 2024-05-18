/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Obj.cpp
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Obj.hpp"
#include "Quad.hpp"
#include "Scene.hpp"
#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "DiffuseLight.hpp"
#include "Metal.hpp"
#include "Isotropic.hpp"
#include "BvhNode.hpp"

namespace rtx
{
    void Scene::registerObj(const libconfig::Setting &obj)
    {
        std::string filepath;
        std::string mat;
        std::string matName;

        if (!obj.exists("filepath"))
            return;

        obj.lookupValue("filepath", filepath);
        obj.lookupValue("material", mat);
        if (registerMaterial(obj, mat, matName))
            return;

        std::shared_ptr<Hittable> hittable =
                Factory::createHittable<Obj>(filepath, _materialMap[matName]);

        std::shared_ptr<Triangle> trianglePtr = std::dynamic_pointer_cast<Triangle>(hittable);

        hittable = registerMatrices(obj, hittable);

        if (mat == "DiffuseLight") {
            _lights.add(hittable);
            _hasLights = true;
        }

        _world.add(Factory::createHittable<BvhNode>(hittable));
    }
};
