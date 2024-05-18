/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Triangle.cpp
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Scene.hpp"
#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "DiffuseLight.hpp"
#include "Metal.hpp"
#include "Isotropic.hpp"
#include "ImageTexture.hpp"

namespace rtx
{
    void Scene::registerTriangle(const libconfig::Setting &triangle)
    {
        Vec3 a;
        Vec3 b;
        Vec3 c;
        std::string mat;
        std::string matName;

        for (auto &element : triangle) {
            const std::string name(element.getName());
            if (name == "a" && element.exists("x") && element.exists("y") && element.exists("z")) {
                element.lookupValue("x", a[0]);
                element.lookupValue("y", a[1]);
                element.lookupValue("z", a[2]);
            }
            if (name == "b" && element.exists("x") && element.exists("y") && element.exists("z")) {
                element.lookupValue("x", b[0]);
                element.lookupValue("y", b[1]);
                element.lookupValue("z", b[2]);
            }
            if (name == "c" && element.exists("x") && element.exists("y") && element.exists("z")) {
                element.lookupValue("x", c[0]);
                element.lookupValue("y", c[1]);
                element.lookupValue("z", c[2]);
            }
        }
        triangle.lookupValue("material", mat);
        if (registerMaterial(triangle, mat, matName))
            return;
        std::shared_ptr<Hittable> hittablePtr = Factory::createHittable<Triangle>(a, b, c, _materialMap[matName]);

        hittablePtr = registerMatrices(triangle, hittablePtr);

        Point3 minPoint(
            fmin(a.x(), fmin(b.x(), c.x())),
            fmin(a.y(), fmin(b.y(), c.y())),
            fmin(a.z(), fmin(b.z(), c.z()))
        );
        Point3 maxPoint(
            fmax(a.x(), fmax(b.x(), c.x())),
            fmax(a.y(), fmax(b.y(), c.y())),
            fmax(a.z(), fmax(b.z(), c.z()))
        );

        auto &worldPartMap = getWorldPart(minPoint.x(), minPoint.y(), minPoint.z());

        for (auto &cluster : worldPartMap) {
            auto &points = cluster.first;
            const auto &minClusterPoint = points.first;
            const auto &maxClusterPoint = points.second;

            if (minPoint.x() < maxClusterPoint.x() && minPoint.y() < maxClusterPoint.y() && minPoint.z() < maxClusterPoint.z() &&
                maxPoint.x() > minClusterPoint.x() && maxPoint.y() > minClusterPoint.y() && maxPoint.z() > minClusterPoint.z()) {

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
                checkConstantMedium(triangle, hittablePtr, temp);
                worldPartMap[newPoints] = temp;
                return;
            }
        }

        checkConstantMedium(
            triangle,
            hittablePtr,
            worldPartMap[{minPoint, maxPoint}]
        );
    }
};
