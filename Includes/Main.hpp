/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Main
*/

#ifndef MAIN_HPP_
    #define MAIN_HPP_
    // World
    #include "Camera.hpp"
    #include "Scene.hpp"

    // Utils
    #include "HittableList.hpp"
    #include "Factory.hpp"

    // Materials
    #include "Lambertian.hpp"
    #include "DiffuseLight.hpp"
    #include "ConstantMedium.hpp"
    #include "ImageTexture.hpp"
    #include "Dielectric.hpp"

    // Primitives
    #include "Sphere.hpp"
    #include "Quad.hpp"
    #include "Box.hpp"
    #include "Cylinder.hpp"
    #include "UnlimitedCylinder.hpp"
    #include "Cone.hpp"
    #include "UnlimitedCone.hpp"
    #include "Torus.hpp"
    #include "BvhNode.hpp"
    #include "Triangle.hpp"
    #include "Obj.hpp"

    // Matrix
    #include "RotateY.hpp"
    #include "Translate.hpp"

    // Display
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>


#endif /* !MAIN_HPP_ */
