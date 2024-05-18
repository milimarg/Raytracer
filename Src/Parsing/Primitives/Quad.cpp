/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Quad.cpp
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
    void Scene::registerQuad(const libconfig::Setting &quad, Quad::Type type)
    {
        double x, y, z = 0;
        Point3 q;
        Vec3 u, v;
        std::string mat;
        std::string matName;

        for (auto &element : quad) {
            const std::string name(element.getName());
            if (name == "q" && element.exists("x") && element.exists("y") && element.exists("z")) {
                element.lookupValue("x", x);
                element.lookupValue("y", y);
                element.lookupValue("z", z);
                q = Point3(x, y, z);
            }
            if (name == "u" && element.exists("x") && element.exists("y") && element.exists("z")) {
                element.lookupValue("x", x);
                element.lookupValue("y", y);
                element.lookupValue("z", z);
                u = Vec3(x, y, z);
            }
            if (name == "v" && element.exists("x") && element.exists("y") && element.exists("z")) {
                element.lookupValue("x", x);
                element.lookupValue("y", y);
                element.lookupValue("z", z);
                v = Vec3(x, y, z);
            }
        }

        if (type == Quad::Type::STANDARD) {
            quad.lookupValue("material", mat);
            if (registerMaterial(quad, mat, matName))
                return;
            matName = mat == "light" ? mat : matName;
        } else
            _hasLights = true;

        const std::string newMatName = type == Quad::Type::STANDARD ? matName : "m";

        std::shared_ptr<Hittable> hittable;

        if (quad.exists("normalmap")) {
            std::string path;

            quad.lookupValue("normalmap", path);
            hittable = Factory::createHittable<Quad>(q, u, v, _materialMap[newMatName], std::make_shared<ImageTexture>(path));
        } else {
            hittable = Factory::createHittable<Quad>(q, u, v, _materialMap[newMatName]);
        }

        hittable = registerMatrices(quad, hittable);

        if (mat == "DiffuseLight") {
            _lights.add(hittable);
            _hasLights = true;
        }

        if (type == Quad::Type::LIGHT) {
            _lights.add(hittable);
            return;
        }

        static constexpr double clusterThreshold = 50.0;

        auto &worldPartMap = getWorldPart(q.x(), q.y(), q.z());

        Vec3 halfU = 0.5 * u;
        Vec3 halfV = 0.5 * v;
        Point3 q1 = q - halfU - halfV;
        Point3 q2 = q + halfU - halfV;
        Point3 q3 = q + halfU + halfV;
        Point3 q4 = q - halfU + halfV;

        Point3 minPoint(
            std::min({q1.x(), q2.x(), q3.x(), q4.x()}),
            std::min({q1.y(), q2.y(), q3.y(), q4.y()}),
            std::min({q1.z(), q2.z(), q3.z(), q4.z()})
        );
        Point3 maxPoint(
            std::max({q1.x(), q2.x(), q3.x(), q4.x()}),
            std::max({q1.y(), q2.y(), q3.y(), q4.y()}),
            std::max({q1.z(), q2.z(), q3.z(), q4.z()})
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
                    quad,
                    hittable,
                    temp
                );
                worldPartMap[newPoints] = temp;
                return;
            }
        }

        checkConstantMedium(
            quad,
            hittable,
            worldPartMap[{minPoint, maxPoint}]
        );
    }
}
