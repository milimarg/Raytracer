/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Box.cpp
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Box.hpp"
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
    void Scene::registerBox(const libconfig::Setting &box)
    {
        Vec3 posUpLeft;
        Vec3 posDownRight;
        std::string mat;
        std::string matName;

        if (!box.exists("positionUpLeft") || !box.exists("positionDownRight"))
            return;

        box["positionUpLeft"].lookupValue("x", posUpLeft[0]);
        box["positionUpLeft"].lookupValue("y", posUpLeft[1]);
        box["positionUpLeft"].lookupValue("z", posUpLeft[2]);
        box["positionDownRight"].lookupValue("x", posDownRight[0]);
        box["positionDownRight"].lookupValue("y", posDownRight[1]);
        box["positionDownRight"].lookupValue("z", posDownRight[2]);
        box.lookupValue("material", mat);
        if (registerMaterial(box, mat, matName))
            return;

        std::shared_ptr<Hittable> hittable;

        if (box.exists("normalmap")) {
            std::string path;

            box.lookupValue("normalmap", path);
            hittable = Factory::createHittable<Box>(posUpLeft, posDownRight, _materialMap[matName], std::make_shared<ImageTexture>(path));
        } else {
            hittable = Factory::createHittable<Box>(posUpLeft, posDownRight, _materialMap[matName]);
        }

        hittable = registerMatrices(box, hittable);

        if (mat == "DiffuseLight") {
            _lights.add(hittable);
            _hasLights = true;
        }

        static constexpr double clusterThreshold = 50.0;

        auto &worldPartMap = getWorldPart(posUpLeft.x(), posUpLeft.y(), posUpLeft.z());

        Point3 minPoint(
            std::min(posUpLeft.x(), posDownRight.x()),
            std::min(posUpLeft.y(), posDownRight.y()),
            std::min(posUpLeft.z(), posDownRight.z())
        );
        Point3 maxPoint(
            std::max(posUpLeft.x(), posDownRight.x()),
            std::max(posUpLeft.y(), posDownRight.y()),
            std::max(posUpLeft.z(), posDownRight.z())
        );

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
                    box,
                    hittable,
                    temp
                );
                worldPartMap[newPoints] = temp;
                return;
            }
        }

        checkConstantMedium(
            box,
            hittable,
            worldPartMap[{minPoint, maxPoint}]
        );
    }
};
