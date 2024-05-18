/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Obj.cpp
*/

#include <fstream>
#include <sstream>
#include "../../Includes/Obj.hpp"

namespace rtx
{
    Obj::Obj(const std::string &filepath, std::shared_ptr<Material> mat)
        : _filepath(filepath), _mat(mat)
    {
        parse();

        for (Triangle &triangle : _triangles) {
            std::shared_ptr<Hittable> hittablePtr = Factory::createHittable<Triangle>(triangle);
            add(hittablePtr);
        }
    }

    Obj::~Obj() {}

    void Obj::parse()
    {
        std::ifstream file(_filepath);

        if (!file.is_open()) {
            std::cerr << "Failed to open OBJ file \"" << _filepath << "\"" << std::endl;
            return;
        }
        std::vector<Vec3> vertices;
        char line[256];
        char trash;

        while (!file.eof()) {
            file.getline(line, 255);
            std::stringstream s;
            s << line;
            if (line[0] == 'v') {
                Vec3 v;
                s >> trash >> v[0] >> v[1] >> v[2];
                vertices.push_back(v);
            }
            if (line[0] == 'f') {
                int f[3];
                s >> trash >> f[0] >> f[1] >> f[2];
                Vec3 A = vertices[f[0] - 1];
                Vec3 B = vertices[f[1] - 1];
                Vec3 C = vertices[f[2] - 1];
                Triangle tri(A,
                             B,
                             C,
                             _mat);
                _triangles.push_back(tri);
            }
        }
        file.close();
    }

    std::shared_ptr<Hittable> Obj::applyTransformation(const rtx::Matrix &matrix)
    {
        std::shared_ptr<Obj> objPtr = Factory::createHittable<Obj>(_filepath, _mat);

        Obj &objRef = *objPtr;

        objRef * matrix;

        return objPtr;
    }

    Obj &Obj::operator*(const rtx::Matrix &matrix)
    {
        std::vector<Triangle> newTriangles;

        for (Triangle &triangle : _triangles)
            newTriangles.push_back(triangle * matrix);

        _triangles.clear();

        _bbox = Aabb();

        for (Triangle &triangle : newTriangles)
            add(Factory::createHittable<Triangle>(triangle));
        return *this;
    }
};
