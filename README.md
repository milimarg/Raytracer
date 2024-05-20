# Raytracer

This repository contains the source code for our raytracer project implemented in C++, which supports various features including but not limited to materials, lighting models, and advanced primitives.

## Features

### Materials

- Dielectric
- Isotropic
- Lambertian
- Metal

### Lighting models

- Diffuse lights
- Ambient light
- Specular reflections

### Supported primitives

- Sphere
- Plane
- Cylinder
- Cone
- Unlimited Cylinder
- Unlimited Cone
- Box
- Triangle
- .obj files

### Transformations (matrix based)

- Translation
- Rotation (X, Y, Z)
- Scale

### Lighting

- Directional light
- Ambient light
- Drop shadows

### Additional features

- Phong reflection model
- Ambient occlusion
- Transparency, refraction, reflection in materials
- Texturing from file or procedural generation
- Normal mapping

### Performance optimizations

- Adaptive supersampling
- Multithreading
- Clustering
- Space partitioning

## Directory structure

The project is organized as follows:

- **Includes**: Contains the header files.
- **Src**: Contains the source files.
- **plugins**: Contains source code for plugins.
- **Assets**: Contains assets usable for configurations.
- **Doc**: Contains the documentation.
- **scenes**: Contains the scene `.cfg` files.

## Building the project

The project can be built using the provided Makefile. To compile the source code and produce an executable named `raytracer`, run the following command in the terminal:

```bash
make
```

## Configuration file

We use libconfig++ for parsing config files (.cfg). Below is an example configuration for a scene:

```cfg
image:
{
    aspectRatio = 1.0;
    imageWidth = 400;
    samplesPerPixel = 400;
    maxDepth = 50;
    background = { r = 0.0; g = 0.0; b = 0.0; };
    adaptativeSupersampling = { activated = true, threshold = 10.0 };
}

camera:
{
    position = { x = 278.0; y = 278.0; z = -765.0; };
    observation_position = { x = 278.0; y = 278.0; z = 0.0; };
    fieldOfView = 40.0;
};

primitives:
{
    spheres = (
        { x = 190.0; y = 90.0; z = 190.0; r = 90.0; material = "Dielectric"; intensity = 1.5; },
        { x = 240.0; y = 300.0; z = 500.0; r = 90.0; material = "Lambertian"; color = { r = 0.65; g = 0.05; b = 0.05; } }
    );
    quads = (
        { q = { x = 555.0; y = 0.0; z = 0.0; }; u = { x = 0.0; y = 0.0; z = 555.0; }; v = { x = 0.0; y = 555.0; z = 0.0; }; material = "Lambertian"; color = { r = 1.0; g = 0.0; b = 0.5; } },
        { q = { x = 0.0; y = 0.0; z = 555.0; }; u = { x = 0.0; y = 0.0; z = -555.0; }; v = { x = 0.0; y = 555.0; z = 0.0; }; material = "Lambertian"; color = { r = 1.0; g = 0.0; b = 0.5; } },
        { q = { x = 0.0; y = 555.0; z = 0.0; }; u = { x = 555.0; y = 0.0; z = 0.0; }; v = { x = 0.0; y = 0.0; z = 555.0; }; material = "Lambertian"; color = { r = 1.0; g = 0.0; b = 0.5; } },
        { q = { x = 0.0; y = 0.0; z = 555.0; }; u = { x = 555.0; y = 0.0; z = 0.0; }; v = { x = 0.0; y = 0.0; z = -555.0; }; material = "Dielectric"; intensity = 1.5 },
        { q = { x = 555.0; y = 0.0; z = 555.0; }; u = { x = -555.0; y = 0.0; z = 0.0; }; v = { x = 0.0; y = 555.0; z = 0.0; }; material = "Lambertian"; color = { r = 1.0; g = 0.0; b = 0.5; } },
        { q = { x = 213.0; y = 554.0; z = 227.0; }; u = { x = 130.0; y = 0.0; z = 0.0; }; v = { x = 0.0; y = 0.0; z = 105.0; }; material = "DiffuseLight"; color = { r = 15.0; g = 15.0; b = 15.0; } }
    );
    lights = (
        { q = { x = 343.0; y = 554.0; z = 332.0; }; u = { x = -130.0; y = 0.0; z = 0.0; }; v = { x = 0.0; y = 0.0; z = -105.0; }; }
    );
}
```

## Contributing

If you wish to contribute to the project, you can follow these guidelines:

- [Adding a Hittable](Doc/md/ADDING-HITTABLE.md)
- [Adding a Material](Doc/md/ADDING-MATERIAL.md)
- [Adding a Plugin](Doc/md/ADDING-PLUGIN.md)

## Plugins

The project includes two plugins: LowResFilter and MedianFilter. You can build them using their respective Makefiles in the plugins/code directory.

## Renders

[Renders](./RENDERS.md)

## Mark

59.5 / 59.5 (100%)

## Credits

[Augustin GROSNON](https://github.com/augustin-grosnon) \
[Noé TRITSCH](https://github.com/NeonMagique) \
[Florent GUITTRE](https://github.com/milimarg)
