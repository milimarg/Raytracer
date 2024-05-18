/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** UnlimitedCone
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
#include "UnlimitedCone.hpp"
#include "ImageTexture.hpp"

namespace rtx
{
    void Scene::registerUnlimitedCone(const libconfig::Setting &cone)
    {
        Point3 origin;
        std::string mat;
        std::string matName;

        if (!cone.exists("center"))
            return;

        cone["center"].lookupValue("x", origin[0]);
        cone["center"].lookupValue("y", origin[1]);
        cone["center"].lookupValue("z", origin[2]);
        cone.lookupValue("material", mat);
        if (registerMaterial(cone, mat, matName))
            return;

        std::shared_ptr<Hittable> hittable;

        if (cone.exists("normalmap")) {
            std::string path;

            cone.lookupValue("normalmap", path);
            hittable = Factory::createHittable<UnlimitedCone>(origin, _materialMap[matName], std::make_shared<ImageTexture>(path));
        } else {
            hittable = Factory::createHittable<UnlimitedCone>(origin, _materialMap[matName]);
        }

        hittable = registerMatrices(cone, hittable);

        if (mat == "DiffuseLight") {
            _lights.add(hittable);
            _hasLights = true;
        }

        static constexpr double clusterThreshold = 50.0;

        auto &worldPartMap = getWorldPart(origin.x(), origin.y(), origin.z());

        Point3 minPoint(origin.x(), origin.y(), origin.z());
        Point3 maxPoint(origin.x(), origin.y(), origin.z());

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
                    cone,
                    hittable,
                    temp
                );
                worldPartMap[newPoints] = temp;
                return;
            }
        }

        checkConstantMedium(
            cone,
            hittable,
            worldPartMap[{minPoint, maxPoint}]
        );
    }
};
