/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** ConstantMedium
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Cylinder.hpp"
#include "Quad.hpp"
#include "Scene.hpp"
#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "DiffuseLight.hpp"
#include "Metal.hpp"
#include "Isotropic.hpp"
#include "ConstantMedium.hpp"

namespace rtx
{
    void Scene::checkConstantMedium(
        const libconfig::Setting &parent,
        std::shared_ptr<Hittable> container,
        HittableList &list
    )
    {
        bool addBaseElem = true;

        if (parent.exists("constantmedium")) {
            const libconfig::Setting &constantmedium = parent.lookup("constantmedium");

            addBaseElem = registerConstantMedium(
                constantmedium,
                container,
                list
            );
        }

        if (addBaseElem)
            list.add(container);
    }

    bool Scene::registerConstantMedium(
        const libconfig::Setting &medium,
        std::shared_ptr<Hittable> boundary,
        HittableList &list
    )
    {
        double density = 0.0;
        std::string texturePath;
        Color color;
        bool displayContainer = false;
        std::shared_ptr<Texture> texture = nullptr;

        if (!medium.exists("density") || (!medium.exists("color") && !medium.exists("texture")) || !medium.exists("displayContainer"))
            return true;

        medium.lookupValue("density", density);
        medium.lookupValue("displayContainer", displayContainer);

        if (medium.exists("color")) {
            const libconfig::Setting &colorSetting = medium["color"];
            double r, g, b;
            colorSetting.lookupValue("r", r);
            colorSetting.lookupValue("g", g);
            colorSetting.lookupValue("b", b);
            color = Color(r, g, b);
        } else if (medium.exists("texture")) {
            std::string mat;
            std::string matName;

            texture = getMaterialTexture(medium, mat, matName);
        }

        std::shared_ptr<Hittable> hittable;
        if (texture)
            hittable = Factory::createHittable<ConstantMedium>(boundary, density, texture);
        else
            hittable = Factory::createHittable<ConstantMedium>(boundary, density, color);

        list.add(hittable);

        return displayContainer;
    }
};
