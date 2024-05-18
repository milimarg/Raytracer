# Adding a new plugin to the raytracer

In this tutorial, we'll walk through the process of adding a new plugin to the raytracer project. Plugins extend the functionality of the raytracer by providing additional features or filters that can be applied to rendered images.

## Prerequisites

Before getting started, make sure you have:

- Basic understanding of C++ programming
- Familiarity with the raytracer project structure

## Step 1: Create the plugin

The first step is to create a new plugin for the raytracer. The plugin should be implemented as a shared library (.so file) and placed in the "plugins/code" directory.

## Step 2: Implement the plugin interface

Each plugin should implement the `IPlugin` interface, which defines a method for applying the plugin's filter to an image.

```cpp
class IPlugin {
public:
    virtual ~IPlugin() = default;

    virtual std::vector<Color> applyFilter(const std::vector<Color> &pixelBuffer, size_t imageWidth, size_t imageHeight, double threshold) const = 0;
};
```

## Step 3: Build the plugin

Write a Makefile for the plugin and ensure that it builds the shared library (.so file) and places it in the "plugins/bin" directory.

## Step 4: Configure the plugin in the scene

Once the plugin is built, it needs to be configured in the scene. This involves adding the plugin to the plugins configuration in the scene configuration file (typically a `.cfg` file).

```cfg
plugins = {
    myPlugin = {
        name = "myplugin.so";
        // Additional parameters
    };
}
```

## Step 5: Build and test

After implementing and configuring the plugin, build the project and test it in the raytracer. Ensure that the plugin functions correctly and integrates seamlessly with the raytracer.

## Conclusion

Congratulations! You've successfully added a new plugin to the raytracer project. Feel free to explore further and add more plugins or contribute to other aspects of the project.
