/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Scene.c
*/

#include "Camera.hpp"
#include "Factory.hpp"
#include "Sphere.hpp"
#include "Quad.hpp"
#include "Scene.hpp"
#include "BvhNode.hpp"
#include "Torus.hpp"
#include "Lambertian.hpp"

namespace rtx
{
    Scene &Scene::getInstance()
    {
        static Scene instance;

        return instance;
    }

    Scene::Scene()
        : _hasLights(false),
        _worldParts({
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})),
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})),
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})),
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})),
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})),
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})),
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})),
            std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({}))
        })
    {
        _availableSfmlKeys["o"] = sf::Keyboard::Key::O;
        _availableSfmlKeys["e"] = sf::Keyboard::Key::E;
        _availableSfmlKeys["u"] = sf::Keyboard::Key::U;
        _availableSfmlKeys["i"] = sf::Keyboard::Key::I;
        _availableSfmlKeys["z"] = sf::Keyboard::Key::Z;
        _availableSfmlKeys["q"] = sf::Keyboard::Key::Q;
        _availableSfmlKeys["s"] = sf::Keyboard::Key::S;
        _availableSfmlKeys["d"] = sf::Keyboard::Key::D;
    }

    Scene::~Scene() {}

    void Scene::render()
    {
        _camera.render(_world, _lights);
    }

    void Scene::parseElementPerName(const libconfig::Setting &element)
    {
        const std::string name(element.getName());

        if (name == "image")
            registerImage(element);
        if (name == "camera")
            registerCamera(element);
        if (name == "primitives")
            registerPrimitives(element);
        if (name == "subscenes")
            registerSubscenes(element);
    }

    void Scene::parseElementType(const libconfig::Setting &element)
    {
        switch (element.getType()) {
            case libconfig::Setting::TypeInt:
                break;
            case libconfig::Setting::TypeInt64:
                break;
            case libconfig::Setting::TypeFloat:
                break;
            case libconfig::Setting::TypeString:
                break;
            case libconfig::Setting::TypeBoolean:
                break;
            default:
                parseElementPerName(element);
        }
    }

    void Scene::parseRecursive(const libconfig::Setting &root)
    {
        int length = root.getLength();

        for (int i = 0; i < length; i += 1) {
            const libconfig::Setting &pair = root[i];
            parseElementType(pair);
            if (pair.isGroup() || pair.isArray())
                parseRecursive(pair);
            if (pair.isList() && pair.getLength() > 0) {
                parseRecursive(pair[0]);
            }
        }
    }

    std::string Scene::getFileName() const
    {
        return _fileName;
    }

    void Scene::parse()
    {
        if (!_fileName.size())
            return;

        HittableList tempWorld = _world;
        HittableList tempLights = _lights;

        _world = HittableList();
        _lights = HittableList();

        _hasLights = false;
        parse(_fileName);

        if (!_hasLights) {
            std::cerr << "Scene - parse - no light in newly loaded scene" << std::endl;
            _world = tempWorld;
            _lights = tempLights;
        }
    }

    bool Scene::parse(const std::string &sceneFilepath)
    {
        _fileName = sceneFilepath;
        try {
            _cfg.readFile(sceneFilepath.c_str());
        } catch (const libconfig::FileIOException &exception) {
            throw Error("Scene - parse - Couldn't open scene file");
            return true;
        } catch (const libconfig::ParseException &exception) {
            throw Error(std::string("Scene - parse - Couldn't parse scene file: ") +
                exception.getFile() + ":" + std::to_string(exception.getLine()) + " - " +
                exception.getError());
            return true;
        }
        parseRecursive(_cfg.getRoot());

        for (auto &part : _worldParts) {
            for(auto &[_, cluster] : part.second) {
                switch (cluster._objects.size()) {
                    case 0:
                        break;
                    case 1:
                        part.first.add(cluster._objects[0]);
                        break;
                    default:
                        part.first.add(Factory::createHittable<BvhNode>(cluster));
                        break;
                }
            }
        }

        for (auto &part : _worldParts) {
            if (part.first._objects.size()) {
                switch (part.first._objects.size()) {
                    case 0:
                        break;
                    case 1:
                        _world.add(part.first._objects[0]);
                        break;
                    default:
                        _world.add(Factory::createHittable<BvhNode>(part.first));
                        break;
                }
            }
        }

        _worldParts.fill(std::make_pair(HittableList(), std::unordered_map<std::pair<Point3, Point3>, HittableList>({})));

        return false;
    }

    bool Scene::getHasLights() const
    {
        return _hasLights;
    }

    std::unordered_map<std::pair<Point3, Point3>, HittableList> &Scene::getWorldPart(int x, int y, int z)
    {
        return _worldParts[(x >= 0 ? 1 : 0) + (y >= 0 ? 2 : 0) + (z >= 0 ? 4 : 0)].second;
    }

    size_t Scene::hash(const char *s)
    {
        return *s ? static_cast<size_t>(*s) + 33 * hash(s + 1) : 5381;
    }
};
