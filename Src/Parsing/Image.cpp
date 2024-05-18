/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** registerImage.cpp
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
#include "LibraryHandler.hpp"

namespace fs = std::filesystem;

namespace rtx
{
    std::unique_ptr<LibraryHandler> loadPlugin(const std::string &pluginPath)
    {
        LibraryHandler handler(pluginPath);

        if (!handler.isOpen()) {
            throw Error("loadPlugin - Failed to open plugin: " + handler.getLastError());
            return nullptr;
        }

        auto entryPoint = handler.getSymbol<std::unique_ptr<IPlugin>>("entryPoint");

        if (!entryPoint) {
            throw Error("loadPlugin - Failed to retrieve entry point symbol from plugin");
            return nullptr;
        }

        return std::make_unique<LibraryHandler>(pluginPath);
    }

    void Scene::parsePlugins(const libconfig::Setting &pluginsConfig)
    {
        for (int i = 0; i < pluginsConfig.getLength(); ++i) {
            const libconfig::Setting &plugin = pluginsConfig[i];
            std::string pluginName;
            if (!plugin.lookupValue("name", pluginName)) {
                throw Error("Scene - parsePlugins - Missing name for plugin in configuration");
                continue;
            }

            std::string pluginPath = "plugins/bin/" + pluginName;

            double pluginThreshold = 0.0;
            plugin.lookupValue("threshold", pluginThreshold);

            auto loadedPlugin = loadPlugin(pluginPath);

            if (loadedPlugin) {
                _camera._filterPlugins.emplace_back(std::move(loadedPlugin), pluginThreshold);
            } else {
                throw Error("Scene - parsePlugins - Failed to load plugin: " + pluginName);
            }
        }
    }

    void Scene::registerImage(const libconfig::Setting &image)
    {
        if (image.exists("background")) {
            const libconfig::Setting &background = image["background"];

            double r = 0;
            double g = 0;
            double b = 0;

            background.lookupValue("r", r);
            background.lookupValue("g", g);
            background.lookupValue("b", b);
            _camera._background = Color(r, g, b);
        }

        if (image.exists("aspectRatio"))
            image.lookupValue("aspectRatio", _camera._aspectRatio);

        if (image.exists("imageWidth"))
            image.lookupValue("imageWidth", _camera._imageWidth);

        if (image.exists("samplesPerPixel"))
            image.lookupValue("samplesPerPixel", _camera._samplesPerPixel);

        if (image.exists("maxDepth"))
            image.lookupValue("maxDepth", _camera._maxDepth);

        if (image.exists("automaticReload"))
            image.lookupValue("automaticReload", _camera._automaticReload);

        if (image.exists("plugins")) {
            const libconfig::Setting &plugins = image["plugins"];
            parsePlugins(plugins);
        }

        if (image.exists("adaptativeSupersampling")) {
            const libconfig::Setting &adaptativeSupersampling = image["adaptativeSupersampling"];

            if (adaptativeSupersampling.exists("activated"))
                adaptativeSupersampling.lookupValue("activated", _camera._adaptativeSupersamplingOn);
            if (adaptativeSupersampling.exists("threshold"))
                adaptativeSupersampling.lookupValue("threshold", _camera._adaptativeSupersamplingThreshold);
            if (adaptativeSupersampling.exists("intensity"))
                adaptativeSupersampling.lookupValue("intensity", _camera._adaptativeSupersamplinngIntensity);
        }

        image.lookupValue("sfmlDisplay", _camera._sfmlDisplay);

        if (image.exists("sfmlKeys")) {
            const libconfig::Setting &sfmlKeys = image["sfmlKeys"];

            if (sfmlKeys.exists("front") && sfmlKeys.exists("back") && sfmlKeys.exists("left") && sfmlKeys.exists("right")) {
                std::string front = sfmlKeys.lookup("front");
                std::string back = sfmlKeys.lookup("back");
                std::string left = sfmlKeys.lookup("left");
                std::string right = sfmlKeys.lookup("right");

                if (_availableSfmlKeys.contains(front))
                    _camera._sfmlKeys[0] = _availableSfmlKeys[front];
                if (_availableSfmlKeys.contains(back))
                    _camera._sfmlKeys[1] = _availableSfmlKeys[back];
                if (_availableSfmlKeys.contains(left))
                    _camera._sfmlKeys[2] = _availableSfmlKeys[left];
                if (_availableSfmlKeys.contains(right))
                    _camera._sfmlKeys[3] = _availableSfmlKeys[right];
            }
        }
    }
};
