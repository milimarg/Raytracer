/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Cylinder.cpp
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
#include "ImageTexture.hpp"

namespace rtx
{
    void Scene::registerCylinder(const libconfig::Setting &cylinder)
    {
        Point3 origin;
        double radius = 0;
        double height = 0;
        std::string mat;
        std::string matName;

        if (!cylinder.exists("center") || !cylinder.exists("radius") || !cylinder.exists("height"))
            return;

        cylinder["center"].lookupValue("x", origin[0]);
        cylinder["center"].lookupValue("y", origin[1]);
        cylinder["center"].lookupValue("z", origin[2]);
        cylinder.lookupValue("radius", radius);
        cylinder.lookupValue("height", height);
        cylinder.lookupValue("material", mat);
        if (registerMaterial(cylinder, mat, matName))
            return;

        std::shared_ptr<Hittable> hittable;

        if (cylinder.exists("normalmap")) {
            std::string path;

            cylinder.lookupValue("normalmap", path);
            hittable = Factory::createHittable<Cylinder>(origin, radius, height, _materialMap[matName], std::make_shared<ImageTexture>(path));
        } else {
            hittable = Factory::createHittable<Cylinder>(origin, radius, height, _materialMap[matName]);
        }

        hittable = registerMatrices(cylinder, hittable);

        if (mat == "DiffuseLight") {
            _lights.add(hittable);
            _hasLights = true;
        }

        static constexpr double clusterThreshold = 50.0;

        auto &worldPartMap = getWorldPart(origin.x(), origin.y(), origin.z());

        Point3 minPoint(origin.x() - radius, origin.y() - radius, origin.z() - height / 2);
        Point3 maxPoint(origin.x() + radius, origin.y() + radius, origin.z() + height / 2);

        for (auto &cluster : worldPartMap) {
            auto &points = cluster.first;
            const auto &minClusterPoint = points.first;
            const auto &maxClusterPoint = points.second;

            if (minPoint.x() < maxClusterPoint.x() + clusterThreshold &&
                minPoint.y() < maxClusterPoint.y() + clusterThreshold &&
                minPoint.z() < maxClusterPoint.z() + clusterThreshold &&
                maxPoint.x() > minClusterPoint.x() - clusterThreshold &&
                maxPoint.y() > minClusterPoint.y() - clusterThreshold &&
                maxPoint.z() > minClusterPoint.z() - clusterThreshold) {

                Point3 newMinPoint(
                    std::min(minPoint.x(), minClusterPoint.x()),
                    std::min(minPoint.y(), minClusterPoint.y()),
                    std::min(minPoint.z(), minClusterPoint.z())
                );

                Point3 newMaxPoint(
                    std::max(maxPoint.x(), maxClusterPoint.x()),
                    std::max(maxPoint.y(), maxClusterPoint.y()),
                    std::max(maxPoint.z(), maxClusterPoint.z())
                );

                std::pair<Point3, Point3> newPoints(newMinPoint, newMaxPoint);

                HittableList temp = worldPartMap[points];

                worldPartMap.erase(points);
                checkConstantMedium(
                    cylinder,
                    hittable,
                    temp
                );
                worldPartMap[newPoints] = temp;
                return;
            }
        }

        checkConstantMedium(
            cylinder,
            hittable,
            worldPartMap[{minPoint, maxPoint}]
        );
    }
};
