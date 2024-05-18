/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Sphere.cpp
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
#include "ImageTexture.hpp"

namespace rtx
{
    void Scene::registerSphere(const libconfig::Setting &sphere)
    {
        double x = 0;
        double y = 0;
        double z = 0;
        double radius = 0;
        std::string mat;
        std::string matName;

        if (!sphere.exists("x") || !sphere.exists("y") || !sphere.exists("z")
            || !sphere.exists("r") || !sphere.exists("material"))
            return;

        sphere.lookupValue("x", x);
        sphere.lookupValue("y", y);
        sphere.lookupValue("z", z);
        sphere.lookupValue("r", radius);
        sphere.lookupValue("material", mat);
        if (registerMaterial(sphere, mat, matName))
            return;

        std::shared_ptr<Hittable> hittable;

        if (sphere.exists("normalmap")) {
            std::string path;

            sphere.lookupValue("normalmap", path);
            hittable = Factory::createHittable<Sphere>(Point3(x, y, z), radius, _materialMap[matName], std::make_shared<ImageTexture>(path));
        } else {
            hittable = Factory::createHittable<Sphere>(Point3(x, y, z), radius, _materialMap[matName]);
        }

        hittable = std::move(registerMatrices(sphere, hittable));

        if (mat == "DiffuseLight") {
            _lights.add(hittable);
            _hasLights = true;
        }

        auto &worldPartMap = getWorldPart(x, y, z);

        static constexpr double clusterThreshold = 75.0;

        for (auto &cluster : worldPartMap) {
            auto &points = cluster.first;
            const auto &minPoint = points.first;
            const auto &maxPoint = points.second;

            if ((std::abs(x - radius - minPoint.x()) < clusterThreshold &&
                std::abs(y - radius - minPoint.y()) < clusterThreshold &&
                std::abs(z - radius - minPoint.z()) < clusterThreshold) ||
                (std::abs(x + radius - maxPoint.x()) < clusterThreshold &&
                std::abs(y + radius - maxPoint.y()) < clusterThreshold &&
                std::abs(z + radius - maxPoint.z()) < clusterThreshold)) {

                Point3 newMinPoint(
                    std::min(x - radius, minPoint.x()),
                    std::min(y - radius, minPoint.y()),
                    std::min(z - radius, minPoint.z())
                );

                Point3 newMaxPoint(
                    std::max(x + radius, maxPoint.x()),
                    std::max(y + radius, maxPoint.y()),
                    std::max(z + radius, maxPoint.z())
                );

                std::pair<Point3, Point3> newPoints(newMinPoint, newMaxPoint);

                HittableList temp = worldPartMap[points];

                worldPartMap.erase(points);
                checkConstantMedium(
                    sphere,
                    hittable,
                    temp
                );
                worldPartMap[newPoints] = temp;
                return;
            }
        }

        checkConstantMedium(
            sphere,
            hittable,
            worldPartMap[
                {
                    Point3(x - radius, y - radius, z - radius),
                    Point3(x + radius, y + radius, z + radius)
                }
            ]
        );
    };
};
