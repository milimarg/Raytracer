/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Torus
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Torus.hpp"
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
    void Scene::registerTorus(const libconfig::Setting &torus)
    {
        double x = 0;
        double y = 0;
        double z = 0;
        double majorRadius = 0;
        double minorRadius = 0;
        std::string mat;
        std::string matName;

        if (!torus.exists("x") || !torus.exists("y") || !torus.exists("z")
            || !torus.exists("rMaj") || !torus.exists("rMin") || !torus.exists("material"))
            return;

        torus.lookupValue("x", x);
        torus.lookupValue("y", y);
        torus.lookupValue("z", z);
        torus.lookupValue("rMaj", majorRadius);
        torus.lookupValue("rMin", minorRadius);
        torus.lookupValue("material", mat);
        if (registerMaterial(torus, mat, matName))
            return;

        std::shared_ptr<Hittable> hittable;

        hittable = Factory::createHittable<Torus>(Point3(x, y, z), majorRadius, minorRadius, _materialMap[matName]);

        hittable = std::move(registerMatrices(torus, hittable));

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

            if ((std::abs(x - majorRadius - minPoint.x()) < clusterThreshold &&
                std::abs(y - majorRadius - minPoint.y()) < clusterThreshold &&
                std::abs(z - majorRadius - minPoint.z()) < clusterThreshold) ||
                (std::abs(x + majorRadius - maxPoint.x()) < clusterThreshold &&
                std::abs(y + majorRadius - maxPoint.y()) < clusterThreshold &&
                std::abs(z + majorRadius - maxPoint.z()) < clusterThreshold)) {

                Point3 newMinPoint(
                    std::min(x - majorRadius, minPoint.x()),
                    std::min(y - majorRadius, minPoint.y()),
                    std::min(z - majorRadius, minPoint.z())
                );

                Point3 newMaxPoint(
                    std::max(x + majorRadius, maxPoint.x()),
                    std::max(y + majorRadius, maxPoint.y()),
                    std::max(z + majorRadius, maxPoint.z())
                );

                std::pair<Point3, Point3> newPoints(newMinPoint, newMaxPoint);

                HittableList temp = worldPartMap[points];

                worldPartMap.erase(points);
                checkConstantMedium(
                    torus,
                    hittable,
                    temp
                );
                worldPartMap[newPoints] = temp;
                return;
            }
        }

        checkConstantMedium(
            torus,
            hittable,
            worldPartMap[
                {
                    Point3(x - majorRadius, y - majorRadius, z - majorRadius),
                    Point3(x + majorRadius, y + majorRadius, z + majorRadius)
                }
            ]
        );
    };
};
