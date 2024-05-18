# Adding a new Material to the raytracer

In this tutorial, we'll walk through the process of adding a new material to the raytracer project. Materials define how objects interact with light, including properties such as color, reflectivity, and transparency.

## Prerequisites

Before getting started, make sure you have:

- Basic understanding of C++ programming
- Familiarity with the raytracer project structure

## Step 1: Implement the Material class

The first step is to create a new class that implements the `Material` interface. This interface defines methods for computing emitted light, scattering behavior, and scattering probability.

```cpp
class MyMaterial : public IMaterial {
public:
    virtual Color emitted(const Ray &rIn, const HitRecord &rec, double u, double v, const Point3 &p) const = 0 {
        // Implement emitted light calculation here
    }

    virtual bool scatter(const Ray &rIn, const HitRecord &rec, ScatterRecord &srec) const = 0 {
        // Implement scattering behavior here
    }

    virtual double scatteringPdf(const Ray &rIn, const HitRecord &rec, const Ray &scattered) const = 0 {
        // Implement scattering probability calculation here
    }
};
```

## Step 2: Configure the Material in the scene

Once the material class is implemented, it needs to be configured in the scene. This involves adding the material type to the primitive configuration in the scene configuration file (typically a `.cfg` file).

```cfg
primitives:
{
    mySphere = (
        {
            x = 190.0;
            y = 90.0;
            z = 190.0;
            r = 90.0;
            material = "MyMaterial";
            intensity = 1.5;
        }
    );
}
```

## Step 3: Build and test

After implementing and configuring the new material, build the project and test it in the raytracer. Ensure that the material behaves as expected and integrates correctly with other components.

## Conclusion

Congratulations! You've successfully added a new material to the raytracer project. Feel free to explore further and add more materials or contribute to other aspects of the project.
