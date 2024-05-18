/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** GetMaterialTexture
*/

#include "Camera.hpp"
#include "Scene.hpp"
#include "ImageTexture.hpp"
#include "CheckerTexture.hpp"
#include "SolidColor.hpp"
#include "NoiseTexture.hpp"
#include "Factory.hpp"

namespace rtx
{
    std::shared_ptr<Texture> Scene::getMaterialTexture(const libconfig::Setting &primitive, const std::string &mat, std::string &matName)
    {
        std::shared_ptr<Texture> texturePtr = nullptr;

        if (primitive.exists("texture")) {
            const libconfig::Setting &textureSetting = primitive["texture"];
            matName += "texture";

            if (textureSetting.exists("type")) {
                matName += "type";

                std::string textureType;
                textureSetting.lookupValue("type", textureType);

                if (textureType == "color") {
                    matName += "color";

                    Color color;
                    if (textureSetting.exists("color")) {
                        const libconfig::Setting &colorSetting = textureSetting["color"];
                        if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                            colorSetting.lookupValue("r", color[0]);
                            colorSetting.lookupValue("g", color[1]);
                            colorSetting.lookupValue("b", color[2]);
                            texturePtr = Factory::createTexture<SolidColor>(color);
                        }

                        matName += std::to_string(color[0]) + ";"
                        + std::to_string(color[1]) + ";"
                        + std::to_string(color[2]);
                    }
                } else if (textureType == "checker") {
                    matName += "checker";

                    double scale;
                    if (textureSetting.exists("scale") && textureSetting.exists("even") && textureSetting.exists("odd")) {
                        const libconfig::Setting &evenSetting = textureSetting["even"];
                        const libconfig::Setting &oddSetting = textureSetting["odd"];
                        std::shared_ptr<Texture> evenTex = getMaterialTexture(evenSetting, mat, matName);
                        std::shared_ptr<Texture> oddTex = getMaterialTexture(oddSetting, mat, matName);

                        textureSetting.lookupValue("scale", scale);

                        matName += std::to_string(scale) + "even" + "odd";

                        texturePtr = Factory::createTexture<CheckerTexture>(scale, evenTex, oddTex);
                    } else if (textureSetting.exists("scale") && textureSetting.exists("c1") && textureSetting.exists("c2")) {
                        Color evenColor;
                        Color oddColor;

                        const libconfig::Setting &c1Setting = textureSetting["c1"];
                        const libconfig::Setting &c2Setting = textureSetting["c2"];

                        if (c1Setting.exists("r") && c1Setting.exists("g") && c1Setting.exists("b")) {
                            c1Setting.lookupValue("r", evenColor[0]);
                            c1Setting.lookupValue("g", evenColor[1]);
                            c1Setting.lookupValue("b", evenColor[2]);
                        }

                        if (c2Setting.exists("r") && c2Setting.exists("g") && c2Setting.exists("b")) {
                            c2Setting.lookupValue("r", oddColor[0]);
                            c2Setting.lookupValue("g", oddColor[1]);
                            c2Setting.lookupValue("b", oddColor[2]);
                        }

                        matName += std::to_string(evenColor[0]) + ";"
                        + std::to_string(evenColor[1]) + ";"
                        + std::to_string(evenColor[2]);

                        matName += std::to_string(oddColor[0]) + ";"
                        + std::to_string(oddColor[1]) + ";"
                        + std::to_string(oddColor[2]);

                        textureSetting.lookupValue("scale", scale);

                        matName += "scale";

                        texturePtr = Factory::createTexture<CheckerTexture>(scale, evenColor, oddColor);
                    }
                } else if (textureType == "perlin") {
                    matName += "perlin";

                    double scale;
                    int type = -1;
                    if (textureSetting.exists("scale")) {
                        textureSetting.lookupValue("scale", scale);
                        if (textureSetting.exists("t"))
                            textureSetting.lookupValue("t", type);

                        matName += std::to_string(scale);
                        matName += std::to_string(type);

                        texturePtr = Factory::createTexture<NoiseTexture>(scale, type);
                    }
                }
            } else if (textureSetting.exists("path")) {
                std::string texturePath;
                textureSetting.lookupValue("path", texturePath);

                matName += texturePath;

                texturePtr = Factory::createTexture<ImageTexture>(texturePath);
            }
        }

        return texturePtr;
    }
};
