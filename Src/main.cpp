/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** main
*/

#include "Main.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Raytracer: command should be ./raytracer <path to scene file>";
        return 84;
    }

    rtx::Scene &scene = rtx::Scene::getInstance();

    try {
        if (scene.parse(argv[1]))
            return 84;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    if (!scene.getHasLights()) {
        std::cerr << "No light in config file" << std::endl;
        return 84;
    }

    try {
        scene.render();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
