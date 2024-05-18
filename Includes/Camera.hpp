/*
** EPITECH PROJECT, 2024
** preparing-raytracer
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_
    #include "Hittable.hpp"
    #include "Material.hpp"
    #include <thread>
    #include <sstream>
    #include <iomanip>
    #include <SFML/Graphics.hpp>
    #include <algorithm>
    #include <array>
    #include <IPlugin.hpp>
    #include <LibraryHandler.hpp>

namespace rtx
{
    class Camera {
        public:
            double _aspectRatio = 1.0f;
            int _imageWidth = 100;
            int _samplesPerPixel = 10;
            int _maxDepth = 10;
            Color _background;

            double _vfov = 90;
            Point3 _lookfrom = Point3(0, 0, 0);
            Point3 _lookat = Point3(0, 0, -1);
            Vec3 _vup = Vec3(0, 1, 0);

            double _defocusAngle = 0;
            double _focusDist = 10;

            bool _adaptativeSupersamplingOn = false;
            double _adaptativeSupersamplingThreshold = 0.0f;
            int _adaptativeSupersamplinngIntensity = 8;

            std::string _sfmlDisplay = "none";
            std::array<sf::Keyboard::Key, 4> _sfmlKeys;

            void render(const Hittable &world, const Hittable &lights);

            std::vector<std::pair<std::unique_ptr<LibraryHandler>, double>> _filterPlugins;

            bool _automaticReload = false;

        private:
            size_t _imageHeight;
            double _pixelSamplesScale;
            int _sqrtSpp;
            double _recipSqrtSpp;
            Point3 _center;
            Point3 _pixel00Loc;
            Vec3 _pixelDeltaU;
            Vec3 _pixelDeltaV;
            Vec3 _u;
            Vec3 _v;
            Vec3 _w;
            Vec3 _defocusDiskU;
            Vec3 _defocusDiskV;
            bool _alreadyRotated = false;
            bool _moved = false;
            Point3 _baseLookfrom;
            Point3 _baseLookat;
            Vec3 _baseVup;
            std::atomic<bool> _threadsRunning = false;

            void initialize();
            Ray getRay(int i, int j, int sI, int sJ, const std::pair<int, double> &samplecount) const;
            Ray getRay(int i, int j) const;
            Vec3 sampleSquareStratified(int sI, int sJ, const std::pair<int, double> &samplecount) const;
            Vec3 sampleSquare() const;
            Vec3 sampleDisk(double radius) const;
            Point3 defocusDiskSample() const;
            Color rayColor(const Ray &r, int depth, const Hittable &world, const Hittable &lights) const;
            void displayProgressBar(std::atomic_ulong &pixelsProcessed);

            std::pair<int, double> determineSampleCount(const Hittable &world, const Hittable &lights, size_t i, size_t j) const;
            void display(const std::vector<Color> &combinedPixelBuffer) const;
            double colorDistance(const Color& c1, const Color& c2) const;

            void renderToPPM(const Hittable &world, const Hittable &lights);
            Color renderPixel(int i, int j, const Hittable &world, const Hittable &lights, int spp, bool checkSuperSampling = true);

            void handleSfmlDisplay(const Hittable &world, const Hittable &lights);
            void saveImageToFile(const std::vector<sf::Uint8> &pixels);
            std::unique_ptr<std::vector<sf::Uint8>> renderSfmlPreview(const Hittable &world, const Hittable &lights, bool lowRes = false);
            void setColorToPixels(const Color& color, size_t pixelIndex, std::vector<sf::Uint8> &pixels);

            void handleMoving(const Hittable &world, const Hittable &lights);
            void handleMoveKeyEvents();
            void handleRotateKeyEvents();
            void moveInDirection(const Vec3 &direction, double speed);
            void moveSideways(double speed);
            void moveVertically(double speed);
            void rotateViewVertically(const Vec3 &axis, double angle);
            void rotateViewHorizontally(const Vec3 &axis, double angle);
            void barrelRoll(const Vec3 &axis, double angle);

            bool checkReload();
    };
};

#endif /* !CAMERA_HPP_ */
