/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Scene.hpp
*/

#ifndef B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_SCENE_HPP
    #define B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_SCENE_HPP
    #include <libconfig.h++>
    #include <iostream>
    #include <array>
    #include <memory>
    #include <unordered_map>
    #include <filesystem>
    #include <SFML/Graphics.hpp>
    #include "Quad.hpp"
    #include <functional>

namespace std {
    template <>
    struct hash<rtx::Point3> {
        size_t operator()(const rtx::Point3 &p) const
        {
            return hash<double>()(p.x()) ^ hash<double>()(p.y()) ^ hash<double>()(p.z());
        }
    };
}

namespace std {
    template <>
    struct hash<std::pair<rtx::Point3, rtx::Point3>> {
        size_t operator()(const std::pair<rtx::Point3, rtx::Point3>& p) const {
            size_t h1 = std::hash<rtx::Point3>()(p.first);
            size_t h2 = std::hash<rtx::Point3>()(p.second);
            return h1 ^ (h2 << 1);
        }
    };
}

namespace rtx
{
    class Scene {
    public:
        ~Scene();

        static Scene &getInstance();

        bool parse(const std::string &sceneFilepath);
        void parse();
        void render();

        Camera &getCamera() { return _camera; }
        HittableList &getWorld() { return _world; }
        HittableList &getLights() { return _lights; }
        bool getHasLights() const;
        std::string getFileName() const;

    private:
        Scene();
        libconfig::Config _cfg;
        Camera _camera;
        std::array<std::pair<HittableList, std::unordered_map<std::pair<Point3, Point3>, HittableList>>, 8> _worldParts;

        HittableList _world;
        HittableList _lights;
        bool _hasLights;

        std::unordered_map<std::pair<Point3, Point3>, HittableList> &getWorldPart(int x, int y, int z);

        std::unordered_map<std::string, sf::Keyboard::Key> _availableSfmlKeys;

        std::unordered_map<std::string, std::shared_ptr<Material>> _materialMap;
        std::string _fileName;

        void parseRecursive(const libconfig::Setting &root);
        void parseElementType(const libconfig::Setting &element);
        void parseElementPerName(const libconfig::Setting &element);

        void registerImage(const libconfig::Setting &image);
        void registerCamera(const libconfig::Setting &camera);

        void parsePlugins(const libconfig::Setting &pluginsConfig);

        bool registerMaterial(const libconfig::Setting &sphere, const std::string &mat, std::string &matName);
        bool registerDielectric(const libconfig::Setting &primitive, const std::string &mat, std::string &matName);
        bool colorBasedMaterial(const libconfig::Setting &primitive, const std::string &mat, std::string &matName);

        std::shared_ptr<Texture> getMaterialTexture(const libconfig::Setting &primitive, const std::string &mat, std::string &matName);

        size_t hash(const char *s);

        void registerPrimitives(const libconfig::Setting &primitives);
        void registerSphere(const libconfig::Setting &sphere);
        void registerQuad(const libconfig::Setting &sphere, Quad::Type type);
        void registerBox(const libconfig::Setting &box);
        void registerCylinder(const libconfig::Setting &cylinder);
        void registerCone(const libconfig::Setting &cone);
        void registerObj(const libconfig::Setting &obj);
        void registerUnlimitedCylinder(const libconfig::Setting &cylinder);
        void registerUnlimitedCone(const libconfig::Setting &cone);
        void registerTriangle(const libconfig::Setting &triangle);
        void registerTorus(const libconfig::Setting &torus);

        void checkConstantMedium(
            const libconfig::Setting &parent,
            std::shared_ptr<Hittable> container,
            HittableList &list
        );
        bool registerConstantMedium(
            const libconfig::Setting &medium,
            std::shared_ptr<Hittable> container,
            HittableList &list
        );

        std::shared_ptr<Hittable> registerMatrices(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable);
        std::shared_ptr<Hittable> registerTranslationMatrix(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable);
        std::shared_ptr<Hittable> registerRotationMatrix(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable);
        std::shared_ptr<Hittable> registerScale(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable);
        std::shared_ptr<Hittable> registerShear(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable);
        std::shared_ptr<Hittable> registerCustom(const libconfig::Setting &primitive, std::shared_ptr<Hittable> hittable);

        void registerSubscenes(const libconfig::Setting &setting);
    };
};

#endif //B_OOP_400_STG_4_1_RAYTRACER_FLORENT_GUITTRE_SCENE_HPP
