/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Camera
*/

#include "Camera.hpp"
#include "ScatterRecord.hpp"
#include "HittablePdf.hpp"
#include "MixturePdf.hpp"
#include "Scene.hpp"
#include "Factory.hpp"
#include <filesystem>
#include <chrono>
#include "BvhNode.hpp"

namespace rtx
{
    using DisplayFunction = void (Camera::*)(const Hittable &, const Hittable &);

    void Camera::render(const Hittable &world, const Hittable &lights)
    {
        initialize();

        _baseLookfrom = _lookfrom;
        _baseLookat = _lookat;
        _baseVup = _vup;

        DisplayFunction displayFunc = nullptr;

        if (_sfmlDisplay == "moving")
            displayFunc = &Camera::handleMoving;
        else if (_sfmlDisplay == "on")
            displayFunc = &Camera::handleSfmlDisplay;
        else
            displayFunc = &Camera::renderToPPM;

        if (displayFunc)
            (this->*displayFunc)(world, lights);
        else
            throw Error("Camera - render - Unknown display mode: " + _sfmlDisplay);
    }

    void Camera::renderToPPM(const Hittable &world, const Hittable &lights)
    {
        std::cout << "P3\n" << _imageWidth << ' ' << _imageHeight << "\n255\n";

        const size_t numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads(numThreads);
        std::atomic<size_t> row(0);
        std::atomic<size_t> pixelsProcessed(0);
        std::vector<std::vector<Color>> threadPixelBuffer(numThreads, std::vector<Color>(_imageWidth * _imageHeight));

        auto renderRow = [&](size_t threadIndex) {
            while (true) {
                size_t j = row.fetch_add(1, std::memory_order_relaxed);
                if (j >= _imageHeight)
                    break;

                for (size_t i = 0; i < _imageWidth; ++i) {
                    threadPixelBuffer[threadIndex][j * _imageWidth + i] = renderPixel(i, j, world, lights, _samplesPerPixel);
                    pixelsProcessed.fetch_add(1, std::memory_order_relaxed);
                }

                if (j % 10 == 0)
                    displayProgressBar(pixelsProcessed);
            }
        };

        for (size_t t = 0; t < numThreads; ++t)
            threads[t] = std::thread(renderRow, t);

        for (auto &thread : threads)
            if (thread.joinable())
                thread.join();

        displayProgressBar(pixelsProcessed);

        std::vector<Color> combinedPixelBuffer(_imageWidth * _imageHeight);
        for (size_t t = 0; t < numThreads; ++t)
            for (size_t i = 0; i < _imageWidth * _imageHeight; ++i)
                combinedPixelBuffer[i] += threadPixelBuffer[t][i];

        for (auto &[pluginHandler, t] : _filterPlugins)
            combinedPixelBuffer = pluginHandler->getSymbol<std::unique_ptr<IPlugin>>("entryPoint")->applyFilter(combinedPixelBuffer, _imageWidth, _imageHeight, t);

        display(combinedPixelBuffer);

        std::clog << std::endl << "Done." << std::endl;
    }

    Color Camera::renderPixel(int i, int j, const Hittable &world, const Hittable &lights, int spp, bool checkSuperSampling)
    {
        Color pixelColor(0, 0, 0);

        std::pair<int, double> samples(spp, 1.0 / spp);
        if (checkSuperSampling && _adaptativeSupersamplingOn)
            samples = determineSampleCount(world, lights, i, j);
        int sqrtSam = int(sqrt(samples.first));

        for (int sJ = 0; sJ < sqrtSam; ++sJ) {
            for (int sI = 0; sI < sqrtSam; ++sI) {
                Ray r = getRay(i, j, sI, sJ, samples);
                pixelColor += rayColor(r, _maxDepth, world, lights);
            }
        }

        return pixelColor * samples.second;
    }

    std::unique_ptr<std::vector<sf::Uint8>> Camera::renderSfmlPreview(const Hittable &world, const Hittable &lights, bool lowRes)
    {
        std::unique_ptr<std::vector<sf::Uint8>> pixels = std::make_unique<std::vector<sf::Uint8>>(_imageWidth * _imageHeight * 4);

        const size_t numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads(numThreads);
        std::atomic<size_t> row(0);
        std::atomic<size_t> pixelsProcessed(0);

        auto renderRow = [&](size_t threadIndex) {
            while (true) {
                size_t j = row.fetch_add(1, std::memory_order_relaxed);
                if (j >= _imageHeight)
                    break;

                for (size_t i = 0; i < _imageWidth; ++i) {
                    size_t pixelIndex = (j * _imageWidth + i) * 4;
                    Color pixelColor = renderPixel(i, j, world, lights, lowRes ? 1 : _samplesPerPixel, !lowRes);
                    setColorToPixels(pixelColor, pixelIndex, *pixels);
                    pixelsProcessed.fetch_add(1, std::memory_order_relaxed);
                }
            }
        };

        for (size_t t = 0; t < numThreads; ++t)
            threads[t] = std::thread(renderRow, t);

        for (auto &thread : threads)
            if (thread.joinable())
                thread.join();

        return pixels;
    }

    bool Camera::checkReload()
    {
        static std::filesystem::file_time_type lastCheckedTime;
        static bool firstTime = true;

        std::filesystem::path filePath = Scene::getInstance().getFileName();

        if (!std::filesystem::exists(filePath))
            return true;

        auto modificationTime = std::filesystem::last_write_time(filePath);

        if (modificationTime != lastCheckedTime) {
            lastCheckedTime = modificationTime;

            if (firstTime) {
                firstTime = false;
                return false;
            }

            return true;
        }

        return false;
    }

    void Camera::handleSfmlDisplay(const Hittable &world, const Hittable &lights)
    {
        unsigned int numThreads = std::thread::hardware_concurrency();

        sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ray tracer");

        sf::Image image;
        if (image.loadFromFile("./Assets/Images/focus.png"))
            window.setIcon(400, 400, image.getPixelsPtr());

        double scaleX = 1920.0 / _imageWidth;
        double scaleY = 1080.0 / _imageHeight;
        double scaleFactor = std::min(scaleX, scaleY);

        size_t scaledWidth = static_cast<size_t>(_imageWidth * scaleFactor);
        size_t scaledHeight = static_cast<size_t>(_imageHeight * scaleFactor);

        int posX = (1920 - scaledWidth) / 2;
        int posY = (1080 - scaledHeight) / 2;

        sf::Sprite sprite;
        sprite.setPosition(posX, posY);

        std::unique_ptr<std::vector<sf::Uint8>> pixels = renderSfmlPreview(world, lights, true);

        sf::Texture texture;
        texture.create(_imageWidth, _imageHeight);
        sprite.setTexture(texture);
        sprite.setScale(scaleFactor, scaleFactor);

        std::atomic<size_t> nextPixelIndex(0);
        std::vector<std::thread> threads = std::vector<std::thread>(numThreads);

        _threadsRunning = true;

        auto renderPixels = [&](size_t threadId) {
            while (_threadsRunning) {
                size_t i = nextPixelIndex.fetch_add(1);
                if (i >= _imageWidth * _imageHeight)
                    break;

                size_t j = i / _imageWidth;
                size_t pixelIndex = (j * _imageWidth + i % _imageWidth) * 4;

                setColorToPixels(renderPixel(i % _imageWidth, j, world, lights, _samplesPerPixel), pixelIndex, *pixels);
            }
        };

        for (size_t t = 0; t < numThreads; ++t)
            threads[t] = std::thread(renderPixels, t);

        while (window.isOpen()) {
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _threadsRunning = false;
                    window.close();
                    saveImageToFile(*pixels);
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::R) {
                    for (auto &thread : threads)
                        if (thread.joinable())
                            thread.join();

                    Scene::getInstance().parse();

                    nextPixelIndex = 0;
                    _threadsRunning = true;

                    for (size_t t = 0; t < numThreads; ++t)
                        threads[t] = std::thread(renderPixels, t);
                }
            }

            if (_automaticReload && checkReload()) {
                for (auto &thread : threads)
                    if (thread.joinable())
                        thread.join();

                Scene::getInstance().parse();

                nextPixelIndex = 0;
                _threadsRunning = true;

                for (size_t t = 0; t < numThreads; ++t)
                    threads[t] = std::thread(renderPixels, t);
            }

            texture.update(pixels->data());
            window.clear(sf::Color::Black);
            window.draw(sprite);
            window.display();
        }

        for (auto &thread : threads)
            if (thread.joinable())
                thread.join();
    }

    void Camera::setColorToPixels(const Color& color, size_t pixelIndex, std::vector<sf::Uint8> &pixels)
    {
        double r = color.r();
        double g = color.g();
        double b = color.b();

        if (r != r)
            r = 0.0;
        if (g != g)
            g = 0.0;
        if (b != b)
            b = 0.0;

        r = Color::linearToGamma(r);
        g = Color::linearToGamma(g);
        b = Color::linearToGamma(b);

        static const Interval intensity(0.0, 0.999);
        int rbyte = static_cast<int>(256 * intensity.clamp(r));
        int gbyte = static_cast<int>(256 * intensity.clamp(g));
        int bbyte = static_cast<int>(256 * intensity.clamp(b));

        pixels[pixelIndex] = static_cast<sf::Uint8>(rbyte);
        pixels[pixelIndex + 1] = static_cast<sf::Uint8>(gbyte);
        pixels[pixelIndex + 2] = static_cast<sf::Uint8>(bbyte);
        pixels[pixelIndex + 3] = 255;
    }

    void Camera::handleMoving(const Hittable &world, const Hittable &lights)
    {
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ray tracer");

        window.setFramerateLimit(60);

        sf::Image image;
        if (image.loadFromFile("./Assets/Images/focus.png"))
            window.setIcon(400, 400, image.getPixelsPtr());

        double scaleX = 1920.0 / _imageWidth;
        double scaleY = 1080.0 / _imageHeight;
        double scaleFactor = std::min(scaleX, scaleY);

        size_t scaledWidth = static_cast<size_t>(_imageWidth * scaleFactor);
        size_t scaledHeight = static_cast<size_t>(_imageHeight * scaleFactor);
        int posX = (1920 - scaledWidth) / 2;
        int posY = (1080 - scaledHeight) / 2;

        sf::Sprite sprite;
        sprite.setPosition(posX, posY);

        std::unique_ptr<std::vector<sf::Uint8>> pixels = renderSfmlPreview(world, lights);

        sf::Texture texture;
        texture.create(_imageWidth, _imageHeight);
        texture.update(pixels->data());
        sprite.setTexture(texture);
        sprite.setScale(scaleFactor, scaleFactor);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    saveImageToFile(*pixels);
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Tab) {
                    Point3 savedLookfrom = _lookfrom;
                    Point3 savedLookat = _lookat;
                    Vec3 savedVup = _vup;

                    Scene::getInstance().parse();

                    _lookfrom = savedLookfrom;
                    _lookat = savedLookat;
                    _vup = savedVup;

                    _moved = true;
                }
            }

            if (_automaticReload && checkReload()) {
                Point3 savedLookfrom = _lookfrom;
                Point3 savedLookat = _lookat;
                Vec3 savedVup = _vup;

                Scene::getInstance().parse();

                _lookfrom = savedLookfrom;
                _lookat = savedLookat;
                _vup = savedVup;

                _moved = true;
            }

            if (window.hasFocus()) {
                handleMoveKeyEvents();
                handleRotateKeyEvents();
            }

            initialize();

            if (_moved) {
                pixels = renderSfmlPreview(world, lights);
                texture.update(pixels->data());
                _moved = false;
            }

            window.clear(sf::Color::Black);
            window.draw(sprite);
            window.display();
        }
    }

    void Camera::handleMoveKeyEvents()
    {
        double moveSpeed = 0.08;

        if (sf::Keyboard::isKeyPressed(_sfmlKeys[0]))
            moveInDirection(_lookat - _lookfrom, moveSpeed);
        if (sf::Keyboard::isKeyPressed(_sfmlKeys[1]))
            moveInDirection(_lookfrom - _lookat, moveSpeed / 2);
        if (sf::Keyboard::isKeyPressed(_sfmlKeys[2]))
            moveSideways(-moveSpeed);
        if (sf::Keyboard::isKeyPressed(_sfmlKeys[3]))
            moveSideways(moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            moveVertically(moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            moveVertically(-moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _lookfrom = _baseLookfrom;
            _lookat = _baseLookat;
            _vup = _baseVup;
            _alreadyRotated = false;
            _moved = true;
        }
    }

    void Camera::handleRotateKeyEvents()
    {
        double rotateSpeed = 2.0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rotateViewVertically(_lookat - _lookfrom, -rotateSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rotateViewVertically(_lookat - _lookfrom, rotateSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            rotateViewHorizontally(_vup, -rotateSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            rotateViewHorizontally(_vup, rotateSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            barrelRoll(_lookfrom - _lookat , rotateSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            barrelRoll(_lookat - _lookfrom, rotateSpeed);
    }

    void Camera::moveInDirection(const Vec3 &direction, double speed)
    {
        _lookfrom += speed * std::max(_alreadyRotated * 1000, 1) * direction;
        _lookat += speed * std::max(_alreadyRotated * 1000, 1) * direction;
        _moved = true;
    }

    void Camera::moveSideways(double speed)
    {
        Vec3 right = Vec3::cross(_lookat - _lookfrom, _vup);
        _lookfrom += speed / 4 * std::max(_alreadyRotated * 1000, 1) * right;
        _lookat += speed / 4 * std::max(_alreadyRotated * 1000, 1) * right;
        _moved = true;
    }

    void Camera::moveVertically(double speed)
    {
        Vec3 up = Vec3::unitVector(_vup);
        _lookfrom += speed / 4 * 1000 * up;
        _lookat += speed / 4 * 1000 * up;
        _moved = true;
    }

    void Camera::rotateViewVertically(const Vec3 &axis, double angle)
    {
        _alreadyRotated = true;
        Vec3 viewDir = Point3::unitVector(axis);
        Vec3 newDir = viewDir.rotate(angle, Vec3::cross(viewDir, _vup));
        _lookat = _lookfrom + newDir;
        _moved = true;
    }

    void Camera::rotateViewHorizontally(const Vec3 &axis, double angle)
    {
        _alreadyRotated = true;
        Vec3 viewDir = Point3::unitVector(_lookat - _lookfrom);
        Vec3 newDir = viewDir.rotate(angle, Vec3::unitVector(axis));
        _lookat = _lookfrom + newDir;
        _moved = true;
    }

    void Camera::barrelRoll(const Vec3 &axis, double angle)
    {
        Vec3 newVup = _vup.rotate(angle, Vec3::unitVector(axis));
        _vup = Point3::unitVector(newVup);
        _lookat = _lookfrom + Vec3(_lookat - _lookfrom).rotate(angle, Vec3::unitVector(axis));
        _moved = true;
    }

    void Camera::saveImageToFile(const std::vector<sf::Uint8> &pixels)
    {
        sf::Image image;
        image.create(_imageWidth, _imageHeight, pixels.data());

        if (image.saveToFile("image.png"))
            std::clog << "Image saved to file: image.png" << std::endl;
        else
            throw Error(" Camera - saveImageToFile - Failed to save image to file");
    }

    void Camera::display(const std::vector<rtx::Color> &combinedPixelBuffer) const
    {
        for (size_t j = 0; j < _imageHeight; ++j) {
            for (size_t i = 0; i < _imageWidth; ++i) {
                const Color &pixelColor = combinedPixelBuffer[j * _imageWidth + i];
                Color::writeColor(std::cout, pixelColor);
            }
        }
    }

    std::pair<int, double> Camera::determineSampleCount(const Hittable &world, const Hittable &lights, size_t i, size_t j) const
    {
        const double threshold = _adaptativeSupersamplingThreshold;

        Color centerColor = rayColor(getRay(i, j), _maxDepth, world, lights);
        double pixelContrast = 0.0;
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (i + di >= 0 && i + di < _imageWidth && j + dj >= 0 && j + dj < _imageHeight) {
                    Color neighborColor = rayColor(getRay(i + di, j + dj), _maxDepth, world, lights);
                    pixelContrast += colorDistance(centerColor, neighborColor);
                }
            }
        }

        if (pixelContrast <= threshold) {
            int reducedSampleCount = _adaptativeSupersamplinngIntensity;
            int reducedSampleTotal = std::max(_samplesPerPixel / reducedSampleCount, 1);
            double reducedScale = 1.0 / reducedSampleTotal;

            return std::pair<int, double>(reducedSampleTotal, reducedScale);
        } else {
            return std::pair<int, double>(_samplesPerPixel, _pixelSamplesScale);
        }
    }

    double Camera::colorDistance(const Color& c1, const Color& c2) const
    {
        double dr = c1.r() - c2.r();
        double dg = c1.g() - c2.g();
        double db = c1.b() - c2.b();
        return std::sqrt(dr * dr + dg * dg + db * db);
    }

    void Camera::initialize()
    {
        _imageHeight = size_t(_imageWidth / _aspectRatio);
        _imageHeight = (_imageHeight < 1) ? 1 : _imageHeight;

        _sqrtSpp = int(sqrt(_samplesPerPixel));
        _recipSqrtSpp = 1.0 / _sqrtSpp;
        _pixelSamplesScale = 1.0 / _samplesPerPixel;

        _center = _lookfrom;

        auto theta = Math::degreesToRadians(_vfov);
        auto h = tan(theta / 2);
        auto viewportHeight = 2 * h * _focusDist;
        auto viewportWidth = viewportHeight * (double(_imageWidth) / _imageHeight);

        _w = Vec3::unitVector(_lookfrom - _lookat);
        _u = Vec3::unitVector(Vec3::cross(_vup, _w));
        _v = Vec3::cross(_w, _u);

        Vec3 viewportU = viewportWidth * _u;
        Vec3 viewportV = viewportHeight * -_v;

        _pixelDeltaU = viewportU / _imageWidth;
        _pixelDeltaV = viewportV / _imageHeight;

        auto viewportUpperLeft = _center - (_focusDist * _w) - viewportU / 2 - viewportV / 2;
        _pixel00Loc = viewportUpperLeft + 0.5 * (_pixelDeltaU + _pixelDeltaV);

        auto defocusRadius = _focusDist * tan(Math::degreesToRadians(_defocusAngle / 2));
        _defocusDiskU = _u * defocusRadius;
        _defocusDiskV = _v * defocusRadius;
    }

    Ray Camera::getRay(int i, int j, int sI, int sJ, const std::pair<int, double> &samplecount) const
    {
        auto offset = sampleSquareStratified(sI, sJ, samplecount);
        auto pixelSample = _pixel00Loc
                        + ((i + offset.x()) * _pixelDeltaU)
                        + ((j + offset.y()) * _pixelDeltaV);

        auto rayOrigin = (_defocusAngle <= 0) ? _center : defocusDiskSample();
        auto rayDirection = pixelSample - rayOrigin;
        auto rayTime = Math::randomDouble();

        return Ray(rayOrigin, rayDirection, rayTime);
    }

    Ray Camera::getRay(int i, int j) const
    {
        auto pixelSample = _pixel00Loc + i * _pixelDeltaU + j * _pixelDeltaV;

        auto rayOrigin = (_defocusAngle <= 0) ? _center : defocusDiskSample();
        auto rayDirection = pixelSample - rayOrigin;
        auto rayTime = Math::randomDouble();

        return Ray(rayOrigin, rayDirection, rayTime);
    }

    Vec3 Camera::sampleSquareStratified(int sI, int sJ, const std::pair<int, double> &samplecount) const
    {
        double recipSqrtSpp = 1.0 / int(sqrt(samplecount.first));

        auto px = ((sI + Math::randomDouble()) * recipSqrtSpp) - 0.5;
        auto py = ((sJ + Math::randomDouble()) * recipSqrtSpp) - 0.5;

        return Vec3(px, py, 0);
    }

    Vec3 Camera::sampleSquare() const
    {
        return Vec3(Math::randomDouble() - 0.5, Math::randomDouble() - 0.5, 0);
    }

    Vec3 Camera::sampleDisk(double radius) const
    {
        return radius * Vec3::randomInUnitDisk();
    }

    Point3 Camera::defocusDiskSample() const
    {
        auto p = Vec3::randomInUnitDisk();
        return _center + (p[0] * _defocusDiskU) + (p[1] * _defocusDiskV);
    }

    Color Camera::rayColor(const Ray &r, int depth, const Hittable &world, const Hittable &lights) const
    {
        if (depth <= 0)
            return Color(0, 0, 0);

        HitRecord rec;

        if (!world.hit(r, Interval(0.001, Math::_infinity), rec))
            return _background;

        ScatterRecord srec;
        Color colorFromEmission = rec._mat->emitted(r, rec, rec._u, rec._v, rec._p);

        if (!rec._mat->scatter(r, rec, srec))
            return colorFromEmission;

        if (srec._skipPdf) {
            return srec._attenuation * rayColor(srec._skipPdfRay, depth - 1, world, lights);
        }

        auto lightPtr = Factory::createPdf<HittablePdf>(lights, rec._p);
        MixturePdf p(lightPtr, srec._pdfPtr);

        Ray scattered = Ray(rec._p, p.generate(), r.time());
        auto pdfVal = p.value(scattered.direction());

        double scatteringPdf = rec._mat->scatteringPdf(r, rec, scattered);

        Color sampleColor = rayColor(scattered, depth - 1, world, lights);
        Color colorFromScatter = (srec._attenuation * scatteringPdf * sampleColor) / pdfVal;

        return colorFromEmission + colorFromScatter;
    }

    void Camera::displayProgressBar(std::atomic_ulong &pixelsProcessed)
    {
        double progress = static_cast<double>(pixelsProcessed.load(std::memory_order_relaxed)) / (_imageWidth * _imageHeight) * 100;
        int barWidth = 100;
        std::stringstream progressBar;
        progressBar << "\rProgress: [";
        int pos = barWidth * progress / 100;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos)
                progressBar << "=";
            else if (i == pos)
                progressBar << ">";
            else
                progressBar << " ";
        }
        progressBar << "] " << std::fixed << std::setprecision(2) << progress << "%    " << std::flush;
        std::clog << progressBar.str();
    }
};
